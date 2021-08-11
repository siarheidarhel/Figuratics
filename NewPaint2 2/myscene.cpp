#include "myscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QPen>
#include <QGraphicsLineItem>
#include <QtMath>
#include <QPainter>
#include <QPicture>
#include <QMessageBox>
#include <QLineEdit>
#include <QFont>
#include <QInputDialog>
#include <QTransform>
#include <QString>
#include <QDrag>
#include <QDebug>
#include <QSizeF>
#include<QKeyEvent>




MyScene::MyScene(QObject *parent): QGraphicsScene(parent)
{

myText=nullptr;


}

MyScene::~MyScene()
{


}

//---------------------------------------------------FIGURE_TYPE

void MyScene::setFigureType(int figureType)
{
    figureType_=figureType;
}


//---------------------------------------------------PRESS_EVENT

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if (event->buttons() & !Qt::LeftButton){ return;}
    else {start_point=event->scenePos();

    switch (figureType_) {

   //case Line| Circle| Rectangle | Triangle| Pencil | Points: break;;qDebug("mouse press") ;
    case Text:
              myText=new MyTextClass();
              myText->setTextInteractionFlags(Qt::TextEditorInteraction);
              myText->setFlag(QGraphicsItem::ItemIsFocusable);

              connect(myText, &MyTextClass::lostFocus, this, &MyScene::editorLostFocus);

              connect(myText, &MyTextClass::selectedChange,this, &MyScene::itemSelected);

             // this->addItem(myText);

              figure=myText;
              this->addItem(figure);
              saveContainer_.push_back(figure);

              figure->setPos(event->scenePos());
              update();
                 // emit signalListWidget();
              break;

    case MoveItem:
                 if(items().isEmpty()){return;}

                 if(!items().isEmpty()){
                    if(!selectedItems().isEmpty()){this->clearSelection();}
                    if(items(event->scenePos()).isEmpty()){return;}
                    figure=items(event->scenePos()).first();
                    figure->setFlag(QGraphicsItem::ItemIsMovable,true);
                    figure->setSelected(true);
                    figure->setCursor(Qt::ClosedHandCursor);}break;



    case SelectItem:
                  if(!items().isEmpty())
                  {
                      if(!selectedItems().isEmpty()){this->clearSelection();}
                      if(items(event->scenePos()).isEmpty()){return;}

                      figure=items(event->scenePos()).first(); qDebug()<<items(event->scenePos()).first()->type();
                      figure->setFlag(QGraphicsItem::ItemIsMovable,false);
                      figure->setSelected(true);} break;

     //case Rotation:

     //case ScaleFigure:
     //case FontCnaghe:







    }//---switch

 }


    QGraphicsScene::mousePressEvent(event);




}


//---------------------------------------------------RELEASE_EVENT

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)

        if(!figure)return;


   switch(figureType_)
   {

        case Pencil:savePancil.push_back(&myGroup); break;
        case Text:event->ignore(); /*saveContainer_.push_back(myText); */      qDebug()<<"Text Item Release Ignore";break;
        case MoveItem:figure->setSelected(false);
                      event->ignore();qDebug()<<"Move Item Release Ignore";break;

        case SelectItem: event->ignore(); break;
        case Line:  saveContainer_.push_back(figure);qDebug("saveContainer");break;
        case Circle: saveContainer_.push_back(figure);qDebug("saveContainer");break;


        case Triangle:saveContainer_.push_back(figure);qDebug("saveContainer");break;
        case  Rectangle:saveContainer_.push_back(figure);qDebug("saveContainer");break;
        case  Points:saveContainer_.push_back(figure);qDebug("saveContainer");break;
    }
        figure->setCursor(Qt::ArrowCursor);

        figure=nullptr;

QGraphicsScene::mouseReleaseEvent(event);

}





//---------------------------------------------------KEY_EVENT
void MyScene::keyPressEvent(QKeyEvent *event)
{

     if(figureType_==Text){event->text();  qDebug()<<"Text Input" <<":"<<event->text(); /*QGraphicsScene::keyPressEvent(event);*/}

     if(event->key()==Qt::Key_Up ){

            if(myAt<=(items().count()-1))
              {
                 if(myAt==items().count()-1){ myAt=0; qDebug()<< "++"<<myAt<<" <-->"<<items().count() ;
                     this->clearSelection();
                      items().at(myAt)->setSelected(true);}

              else { emit ++myAt;
                        this->clearSelection();
                        items().at(myAt)->setSelected(true);
                        qDebug()<<"++"<< myAt<<" <-->"<<items().count() ;}
                }
   }


      if(event->key()==Qt::Key_Down ){

              if(myAt<=(items().count()-1))
               {
                    if(myAt==0){ myAt=(items().count()-1); qDebug()<< "--"<<myAt<<" <-->"<<items().count();
                        this->clearSelection();
                         items().at(myAt)->setSelected(true);
               }


               else{ emit --myAt;


                   this->clearSelection();

                    items().at(myAt)->setSelected(true);
                    //figure=saveContainer_.at(myAt);

                    qDebug()<< "--"<<myAt<<" <-->"<<items().count() ;}
         }
    }
QGraphicsScene::keyPressEvent(event);
}







//---------------------------------------------------MOVE_EVENT

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(event==nullptr) return;
 if (event->buttons() & Qt::LeftButton){

   qDebug()<<Q_FUNC_INFO;



  switch (figureType_) {


   case Line:end_point =event->scenePos(); drawLine();emit signalListWidget(); break;
   case Rectangle:end_point =event->scenePos(); drawRect();emit signalListWidget();  break;
   case Triangle:end_point =event->scenePos(); drawTriangle();emit signalListWidget(); break;
   case Pencil:end_point =event->scenePos(); drawPencile(); break;
   case SelectItem: event->ignore(); break;
   case Circle: end_point =event->scenePos(); drawCircle(); emit signalListWidget();  break;
   case Points:end_point =event->scenePos();drawPoints(); break;
   case Text: break;
   case MoveItem:
         {         if(saveContainer_.isEmpty()){

                       QWidget *my = nullptr;
                       QMessageBox::information (my,(""), tr("No OBJECT to move"),  QMessageBox::Ok);

                       delete my;
                       return; }

                   else  {
                         if(selectedItems().isEmpty()){event->ignore(); qDebug()<<"MoVE SELECT IGNORE"; return;}
                          else{ QRectF bbox = figure->boundingRect().normalized();
                                figure->setPos(event->scenePos()-bbox.center());}
                         }
                }break;
             }
      }

QGraphicsScene::mouseMoveEvent(event);
}






//---------------------------------------------------LINE

void MyScene::drawLine()
{
    if(figure){removeItem(figure); figure =nullptr; }

            figure = addLine(start_point.x(), start_point.y(),end_point.x(), end_point.y(),QPen(myPen));
            figure->setOpacity(myOpacity);
            figure->setZValue(myStrartZValue);
            figure->setFlag(QGraphicsItem::ItemIsSelectable,true);
}


//---------------------------------------------------RECT
void MyScene::drawRect(){

    if(figure){delete figure;}


 QRectF rect ( end_point.x() > start_point.x() ?  start_point.x() : end_point.x(),
                    end_point.y() > start_point.y() ? start_point.y() : end_point.y(),
                    qAbs(end_point.x() - start_point.x()),
                    qAbs(end_point.y() - start_point.y()));


    figure= addRect(rect,QPen(myPen),QBrush(myBrush));
    figure->setRotation(myRotate);
    figure->setOpacity(myOpacity);
    figure->setZValue(myStrartZValue);
    figure->setFlag(QGraphicsItem::ItemIsSelectable,true);

}

//---------------------------------------------------TRIANGLE

void MyScene::drawTriangle(){

   if(figure){delete figure;}

 QPolygonF triangle;

        triangle << QPointF(start_point.x() + (end_point.x() > start_point.x() ? + 1 : - 1)*
                               abs((end_point.x() - start_point.x())/2), start_point.y())
                    << QPointF((end_point.x() > start_point.x()) ? end_point.x() : start_point.x(),
                               end_point.y())
                    << QPointF((end_point.x() > start_point.x()) ? start_point.x() : end_point.x(),
                               end_point.y());


      figure = addPolygon(triangle,QPen(myPen),QBrush(myBrush));
      figure->setRotation(myRotate);
      figure->setOpacity(myOpacity);
      figure->setZValue(myStrartZValue);
      figure->setFlag(QGraphicsItem::ItemIsSelectable,true);


}


//---------------------------------------------------CLEAR_SCENE
void MyScene::clearScene(){

    saveContainer_.clear();
    this->clear();
    emit signalListWidget();
     update();
}


//---------------------------------------------------PENCILE

void MyScene::drawPencile(){

qDebug()<<Q_FUNC_INFO;

    figure =  addLine (start_point.rx(), start_point.ry(),end_point.x(), end_point.y(),QPen(myPen));
    start_point=end_point;
    //myGroup.addToGroup(figure);
    figure->setOpacity(myOpacity);
    //figure->setFlags(QGraphicsItem::ItemIsFocusable| QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable );
    figure->setFlag(QGraphicsItem::ItemIsSelectable,true);

}

//---------------------------------------------------CIRCLE
void MyScene::drawCircle(){
    if(figure){removeItem(figure);}

    auto w=end_point.x()-start_point.x();
    auto h=end_point.y()-start_point.y();

    figure= addEllipse(start_point.x(), start_point.y(),w, h,QPen(myPen),QBrush(myBrush));
    figure->setRotation(myRotate);
    figure->setOpacity(myOpacity);
    figure->setZValue(myStrartZValue);
    //figure->setFlag(QGraphicsItem::ItemIsFocusable,true);
    //figure->setFlag(QGraphicsItem::ItemIsMovable,true);
    figure->setFlag(QGraphicsItem::ItemIsSelectable,true);




}

//---------------------------------------------------POINTS
void MyScene::drawPoints(){
    if(figure){delete figure;}

    figure = addEllipse(end_point.x(),end_point.y(),4,4,QPen(Qt::black),QBrush(myBrush));
    figure->setOpacity(myOpacity);
    figure->setFlag(QGraphicsItem::ItemIsSelectable,true);
}

//---------------------------------------------------UNDO
void MyScene::undoMethod(){



          if( this->items().isEmpty()){

             messBox.setIcon(QMessageBox::Information);
             messBox.setText(warnMessage);
             messBox.exec();
             return;}

      this->removeItem(saveContainer_.pop());
      emit signalListWidget();

}




//---------------------------------------------------LINE_COLOUR

void MyScene::colourDial(QColor colour){

    myPen.setColor(colour);


}

//---------------------------------------------------LINE_WIDTH

void MyScene::setLineWidth(int lineWidth){

    myPen.setWidth(lineWidth);
}

//---------------------------------------------------FILL_COLOUR

void MyScene::setFillColour(QColor colourFill){



    if(!items().isEmpty()){
        if(!selectedItems().isEmpty()){
        auto index=items().indexOf(selectedItems().constFirst());

        if(items().at(index)->type()==MyTextClass::Type){
            items().at(index)->setSelected(true);

            QGraphicsTextItem *temp=qgraphicsitem_cast<MyTextClass*> (this->items().at(index));
            temp->setDefaultTextColor(colourFill);
        }

       if (items().at(index)->type()==4)
          {

                QGraphicsEllipseItem *temp1 =qgraphicsitem_cast<QGraphicsEllipseItem*> (this->items().at(index));
                temp1-> setBrush(QBrush(colourFill))  ;
          }

       if (items().at(index)->type()==3)
          {

                QGraphicsRectItem *temp1 =qgraphicsitem_cast<QGraphicsRectItem*> (this->items().at(index));
                temp1-> setBrush(QBrush(colourFill))  ;
          }

       if (items().at(index)->type()==5)
          {

                QGraphicsPolygonItem *temp1 =qgraphicsitem_cast<QGraphicsPolygonItem*> (this->items().at(index));
                temp1-> setBrush(QBrush(colourFill))  ;
          }

    }
  }


    myBrush.setColor(colourFill);
    myBrush.setStyle(Qt::SolidPattern);
    this->update();
}

//---------------------------------------------------OPACITY

void MyScene::myOpacityFunc(float opacity)
{
  emit myOpacity=opacity;
   figure=saveContainer_.constLast();
   figure->setOpacity(myOpacity);
   saveContainer_.push_front(figure);
   figure=nullptr;

   this->update();
}


//---------------------------------------------------BRING_TO_FRONT
void MyScene::bringToFront()
{
    if(!items().isEmpty() & !selectedItems().isEmpty())
   {
    qDebug()<< Q_FUNC_INFO;
    ++myChangeZValue;

    figure=this->selectedItems().first();
    figure->setZValue(myChangeZValue);
    emit signalListWidget();

   }
}


//---------------------------------------------------EDITOR_LOST_FOCUS

void MyScene::editorLostFocus(MyTextClass *myText)
{
qDebug()<<Q_FUNC_INFO;

if (myText->toPlainText().isEmpty()) {
   this->removeItem(myText);
   // myText->deleteLater();
    emit signalListWidget();

    update();
}
 else{

        QTextCursor cursor = myText->textCursor();
        cursor.clearSelection();
       myText->setTextCursor(cursor);
       emit signalListWidget();

   }


}



//---------------------------------------------------ROTATION

void MyScene::rotationFigure(int rotate)
{
   emit myRotate=rotate;
   //if(saveContainer_.isEmpty()){return;}

    if(!this->items().isEmpty()){
       if(this->selectedItems().isEmpty()){this->items().first()->setSelected(true);}
   figure=selectedItems().first();

   QRectF bbox = figure->boundingRect().normalized();
   QPointF center = bbox.center();
     figure->setTransformOriginPoint(center);

   figure->setRotation(myRotate);

   figure=nullptr;

   myRotate=0;
   update();
}
}




//---------------------------------------------------SCALE_FIGURE

void MyScene::scaleFigure(int scale)
{
    figure->setScale(scale);
}












