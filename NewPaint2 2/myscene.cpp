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
              break;

    case MoveItem:
                 if(saveContainer_.isEmpty()){return;}



                       if(this->selectedItems().isEmpty()){
                             if(!items(event->scenePos()).isEmpty()){
                             figure=items(event->scenePos()).first();
                             if(event->buttons()==Qt::LeftButton)
                                {
                                 figure->setSelected(true);

                                 figure->setCursor(Qt::ClosedHandCursor);
                             }}


                 }

                 else {
                    figure=this->selectedItems().first();


                  //auto index=saveContainer_. indexOf(tempItem);

                 //figure=saveContainer_.at(index) ;
                // items().first()->setSelected(false);
                 //figure=items().first();
                                 figure->setCursor(Qt::ClosedHandCursor);

   }


       break;
    }

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
        case Line:  saveContainer_.push_back(figure);qDebug("saveContainer");break;
        case Circle:saveContainer_.push_back(figure);qDebug("saveContainer");break;
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

            if(myAt<=(saveContainer_.count()-1))
        {
                if(myAt==saveContainer_.count()-1){emit myAt=0; qDebug()<< "++"<<myAt<<" <-->"<<saveContainer_.count()-1 ;return;}


                else { emit ++myAt;
                        for(int i=0; i<saveContainer_.size()-1;++i){saveContainer_.at(i)->setSelected(false);}
                       // saveContainer_.at(myAt-1)->setSelected(false);
                       // saveContainer_.at(0)->setSelected(false);
                        saveContainer_.at(myAt)->setSelected(true);
                        qDebug()<<"++"<< myAt<<" <-->"<<saveContainer_.count()-1 ;}
                }
        //}
   }



           if(event->key()==Qt::Key_Down ){

               if(myAt<=(saveContainer_.count()-1))
         {
                    if(myAt==0){emit myAt=(saveContainer_.count()-1); qDebug()<< "--"<<myAt<<" <-->"<<saveContainer_.count()-1 ;return;}


               else{ emit --myAt;
                        for(int i=0; i<saveContainer_.size()-1;++i){saveContainer_.at(i)->setSelected(false);}


                    saveContainer_.at(myAt+1)->setSelected(false);
                    saveContainer_.at(myAt)->setSelected(true);
                    figure=saveContainer_.at(myAt);


                    qDebug()<< "--"<<myAt<<" <-->"<<saveContainer_.count()-1 ;}
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


   case Line:end_point =event->scenePos(); drawLine();figure->setFocus(); break;
   case Rectangle:end_point =event->scenePos(); drawRect(); figure->setFocus(); break;
   case Triangle:end_point =event->scenePos(); drawTriangle();figure->setFocus(); break;
   case Pencil:end_point =event->scenePos(); drawPencile(); break;

   case Circle: end_point =event->scenePos(); drawCircle(); figure->setFocus();  break;
   case Points:end_point =event->scenePos();drawPoints();figure->setFocus(); break;
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
                      // myText->setPos(event->scenePos()-bbox.center());
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
            figure->setFlags(QGraphicsItem::ItemIsFocusable| QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable );
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
    figure->setFlags(QGraphicsItem::ItemIsFocusable| QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable );

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
      figure->setFlags(QGraphicsItem::ItemIsFocusable| QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable );


}


//---------------------------------------------------CLEAR_SCENE
void MyScene::clearScene(){

    saveContainer_.clear();
    //textContainer.clear();
     update();
}


//---------------------------------------------------PENCILE

void MyScene::drawPencile(){

qDebug()<<Q_FUNC_INFO;

    figure =  addLine (start_point.rx(), start_point.ry(),end_point.x(), end_point.y(),QPen(myPen));
    start_point=end_point;
    //myGroup.addToGroup(figure);
    figure->setOpacity(myOpacity);
    figure->setFlags(QGraphicsItem::ItemIsFocusable| QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable );

}

//---------------------------------------------------CIRCLE
void MyScene::drawCircle(){
    if(figure){removeItem(figure);}

    auto w=end_point.x()-start_point.x();
    auto h=end_point.y()-start_point.y();

    figure= addEllipse(start_point.x(), start_point.y(),w, h,QPen(myPen),QBrush(myBrush));
    figure->setRotation(myRotate);
    figure->setOpacity(myOpacity);
    figure->setFlag(QGraphicsItem::ItemIsFocusable,true);
    figure->setFlag(QGraphicsItem::ItemIsMovable,true);
    figure->setFlag(QGraphicsItem::ItemIsSelectable,true);
    //figure->setFlags(QGraphicsItem::ItemIsFocusable| QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable );
    //figure->setSelected(true);
//    figure->setFocus(Qt::ClickFocus);


}

//---------------------------------------------------POINTS
void MyScene::drawPoints(){
    if(figure){delete figure;}

    figure = addEllipse(end_point.x(),end_point.y(),4,4,QPen(Qt::black),QBrush("black"));
    figure->setOpacity(myOpacity);
    figure->setFlags(QGraphicsItem::ItemIsFocusable| QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable );
}

//---------------------------------------------------UNDO
void MyScene::undoMethod(){

    if (figureType_!=Text){

          if( saveContainer_.isEmpty()){

          messBox.setIcon(QMessageBox::Information);
          messBox.setText(warnMessage);
          messBox.exec();
           return;}

      this->removeItem(saveContainer_.pop());}


//    if(figureType_==Text){

//        if(textContainer.isEmpty()){
//            messBox.setIcon(QMessageBox::Information);
//            messBox.setText(warnTextMessage);
//            messBox.exec();
//             return;}
//            this->removeItem(textContainer.pop());}


   }





//---------------------------------------------------COLOUR

void MyScene::colourDial(QColor colour){

    myPen.setColor(colour);


}

//---------------------------------------------------LINE_WIDTH

void MyScene::setLineWidth(int lineWidth){

    myPen.setWidth(lineWidth);
}

//---------------------------------------------------FILL_COLOUR

void MyScene::setFillColour(QColor colourFill){


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


//---------------------------------------------------EDITOR_LOST_FOCUS

void MyScene::editorLostFocus(MyTextClass *myText)
{
qDebug()<<Q_FUNC_INFO;

if (myText->toPlainText().isEmpty()) {
   this->removeItem(myText);
    myText->deleteLater();
    update();
}
 else{

        QTextCursor cursor = myText->textCursor();
        cursor.clearSelection();
       myText->setTextCursor(cursor);
//       myText->setFocus(Qt::MouseFocusReason);

       //figure=myText;
      // saveContainer_.push_back(figure); qDebug()<<saveContainer_.last()<< "FIGURE--"<<figure <<"Text to save";

   }


}



//---------------------------------------------------ROTATION

void MyScene::rotationFigure(int rotate)
{
   emit myRotate=rotate;
   if(saveContainer_.isEmpty()){return;}
 //if(figure==nullptr){return;}
   figure=saveContainer_.at(myAt);
  this->setFocusItem(figure);
     //figure=focusItem();


   QRectF bbox = figure->boundingRect().normalized();
     QPointF center = bbox.center();
     figure->setTransformOriginPoint(center);

   figure->setRotation(myRotate);
   //saveContainer_.push_front(figure);
   figure=nullptr;

   myRotate=0;
   update();

}




//---------------------------------------------------SCALE_FIGURE

void MyScene::scaleFigure(int scale)
{
    figure->setScale(scale);
}












