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



MyScene::MyScene(QObject *parent): QGraphicsScene(parent)
{

myText=nullptr;

}

MyScene::~MyScene()
{


}


void MyScene::setFigureType(int figureType)
{
    figureType_=figureType;
}



void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if (event->buttons() & !Qt::LeftButton){ return;}
    else {start_point=event->scenePos();

    switch (figureType_) {

   //case Line| Circle| Rectangle | Triangle| Pencil | Points: break;;qDebug("mouse press") ;
    case Text:
        myText=new MyTextClass();
        myText->setTextInteractionFlags(Qt::TextEditorInteraction);

        connect(myText, &MyTextClass::lostFocus, this, &MyScene::editorLostFocus);

        connect(myText, &MyTextClass::selectedChange,this, &MyScene::itemSelected);

        addItem(myText);
        myText->setPos(event->scenePos());
        update();
        break;

    case MoveItem:
        if(saveContainer_.isEmpty()){return;}

             figure=saveContainer_.last();
        figure->setFocus((Qt::MouseFocusReason));
        //QGraphicsTextItem *item = qgraphicsitem_cast<MyTextClass *>(selectedItems().first());
        //item->setPos(event->scenePos());
        figure->setCursor(Qt::ClosedHandCursor);
        break;
    }
}
QGraphicsScene::mousePressEvent(event);
//start_point.manhattanLength();


}




void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)

        if(!figure)return;
        saveContainer_.push_back(figure);qDebug("saveContainer");
        figure->setCursor(Qt::ArrowCursor);

    figure=nullptr;

QGraphicsScene::mouseReleaseEvent(event);

}








void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(event==nullptr) return;
 if (event->buttons() & Qt::LeftButton){

   qDebug()<<Q_FUNC_INFO;

//    end_point =event->scenePos();

  switch (figureType_) {

 //end_point =event->scenePos();
   case Line:end_point =event->scenePos();drawLine();break;
   case Rectangle:end_point =event->scenePos();drawRect();break;
   case Triangle:end_point =event->scenePos();drawTriangle();break;
   case Pencil:end_point =event->scenePos();drawPencile();break;
   case Circle: end_point =event->scenePos(); drawCircle();   break;
   case Points:end_point =event->scenePos();drawPoints();  break;
   case Text: break;
   case MoveItem:
                   if(saveContainer_.isEmpty()){
                       QWidget *my = nullptr;
                       QMessageBox::information (my,("Information"), tr("No OBJECT to move"),  QMessageBox::Ok);

                       delete my;
                       return; }

                   else  {
                       //figure->setFocus((Qt::MouseFocusReason));

                       //figure->setCursor(Qt::ClosedHandCursor);
                       QRectF bbox = figure->boundingRect().normalized();
                         QPointF center = bbox.center();
                         figure->setTransformOriginPoint(center);

                        figure->setPos(event->scenePos()-bbox.center());
                      // saveContainer_.last()->setPos(event->scenePos());
                   }
  }
}

}



void MyScene::drawLine()
{
    if(figure){removeItem(figure); figure =nullptr; }

            figure = addLine(start_point.x(), start_point.y(),end_point.x(), end_point.y(),QPen(myPen));
            figure->setOpacity(myOpacity);
            figure->setFlags(QGraphicsItem::ItemIsFocusable| QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable );
}



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



void MyScene::clearScene(){

    saveContainer_.clear();
    //textContainer.clear();
     update();
}




void MyScene::drawPencile(){

//QGraphicsPathItem myPath;

    figure =  addLine (start_point.rx(), start_point.ry(),end_point.x(), end_point.y(),QPen(myPen));
    start_point=end_point;
    figure->setOpacity(myOpacity);
    figure->setFlags(QGraphicsItem::ItemIsFocusable| QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable );

}


void MyScene::drawCircle(){
    if(figure){removeItem(figure);}

    auto w=end_point.x()-start_point.x();
    auto h=end_point.y()-start_point.y();

    figure= addEllipse(start_point.x(), start_point.y(),w, h,QPen(myPen),QBrush(myBrush));
    figure->setRotation(myRotate);
    figure->setOpacity(myOpacity);
    figure->setFlags(QGraphicsItem::ItemIsFocusable| QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable );


}

void MyScene::drawPoints(){
    if(figure){delete figure;}

    figure = addEllipse(end_point.x(),end_point.y(),4,4,QPen(Qt::black),QBrush("black"));
    figure->setOpacity(myOpacity);
    figure->setFlags(QGraphicsItem::ItemIsFocusable| QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable );
}


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







void MyScene::colourDial(QColor colour){

    myPen.setColor(colour);


}

void MyScene::setLineWidth(int lineWidth){

    myPen.setWidth(lineWidth);
}



void MyScene::setFillColour(QColor colourFill){


    myBrush.setColor(colourFill);
    myBrush.setStyle(Qt::SolidPattern);





    this->update();



}



void MyScene::myOpacityFunc(float opacity)
{
  emit myOpacity=opacity;
   figure=saveContainer_.constLast();
   figure->setOpacity(myOpacity);
   saveContainer_.push_front(figure);
   figure=nullptr;

   this->update();
}

void MyScene::editorLostFocus(MyTextClass *myText)
{
qDebug()<<Q_FUNC_INFO;


        QTextCursor cursor = myText->textCursor();
        cursor.clearSelection();
       myText->setTextCursor(cursor);
//       this->clearSelection();
//       figure->setCursor(Qt::ArrowCursor);


        if (myText->toPlainText().isEmpty()) {
           removeItem(myText);
            myText->deleteLater();
            update();
        }


}


void MyScene::rotationFigure(int rotate)
{
   emit myRotate=rotate;
   if(saveContainer_.isEmpty()){return;}

   figure=saveContainer_.last();

   QRectF bbox = figure->boundingRect().normalized();
     QPointF center = bbox.center();
     figure->setTransformOriginPoint(center);

   figure->setRotation(myRotate);
   saveContainer_.push_front(figure);
   figure=nullptr;

   myRotate=0;
   update();

}

void MyScene::scaleFigure(int scale)
{
    figure->setScale(scale);
}







//void MyScene::myDragEvent()
//{


//}


