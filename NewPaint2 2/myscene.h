#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include<QPointF>
#include <QGraphicsItemGroup>
#include <QString>
#include<QGraphicsItem>
#include <QColorDialog>
#include<QStack>
#include <QColor>
#include <QPen>
#include<QBrush>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsTextItem>
#include<figuretype.h>
#include <mytextclass.h>



//class MyTextClass;
class MyScene : public QGraphicsScene
{

    Q_OBJECT
    QGraphicsTextItem *myTextItem;


    int figureType_=0;
    const QString warnMessage ={"No UNDO availible"};
//    const QString warnTextMessage={"No Text object"};
    QPointF start_point;
    QPointF end_point;
    QMessageBox messBox;

    QStack<QGraphicsItem*> saveContainer_;
    QList<QGraphicsItemGroup*> savePancil;
    QGraphicsItemGroup myGroup;
   // QStack<QGraphicsTextItem*> textContainer;

    QColorDialog colourDialog;
   QFont myFont;
    QPen myPen;
    QBrush myBrush;
    int myRotate=0;
    float myOpacity=1.0;

    int myAt=0;


    QString fileName = "testMyfile.png";



    QGraphicsItem *figure=nullptr;
    //QGraphicsItem *tempItem=nullptr;




public:

    explicit MyScene(QObject *parent=nullptr);
    ~MyScene();
    MyTextClass *myText;


        void setFigureType(int figureType);

        void drawLine();

        void drawRect();

        void drawTriangle();

        void drawCircle();

        void drawPencile();

        void drawPoints();

        void undoMethod();

        void colourDial(QColor colour);

        void setLineWidth(int lineWidth);

        void setFillColour(QColor colourFill);
       //void myTextAdd(QString mystring);
//        void editText();
        //void myDragEvent();


        void clearScene();
        void rotationFigure (int rotate);
        void scaleFigure (int scale);

        void myOpacityFunc(float opacity);

public slots:
        void editorLostFocus(MyTextClass *myText);

signals:
        void itemSelected (QGraphicsItem *item);

protected:
        virtual    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
       virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
       void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;
    //void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)override;





       // QGraphicsScene interface
protected:
       virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // MYSCENE_H














