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
//#include <>

enum figureType {Line, Circle, Rectangle, Triangle, Pencil, Points, Text};


class MyScene : public QGraphicsScene
{
    Q_OBJECT
    //QGraphicsTextItem *myTextItem=nullptr;
   // QGraphicsTextItem *myTextItem;
    //QString myText;
    int figureType_=0;
    const QString warnMessage ={"No UNDO availible"};
    QPointF start_point;
    QPointF end_point;
    QMessageBox messBox;

    QStack<QGraphicsItem*> saveContainer_;
    QStack<QGraphicsTextItem*> textContainer;

    QColorDialog colourDialog;

    QPen myPen;
    QBrush myBrush;
    int myRotate=0;


    QString fileName = "testMyfile.png";



    QGraphicsItem *figure=nullptr;





public:
    MyScene(QObject *parent=nullptr);
    ~MyScene();

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
        void drawText(QGraphicsTextItem *myGrText);
        void editText();
        void myDragEvent();

        void clearScene();
        void rotationFigure (int rotate);





protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;
};

#endif // MYSCENE_H














