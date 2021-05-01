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

enum figureType { Line, Circle, Rectangle, Triangle, Pencil, Points};


class MyScene : public QGraphicsScene
{
    Q_OBJECT

    int figureType_ = Line;
    QPointF start_point;
    QPointF end_point;

    QStack<QGraphicsItem*> saveContainer_;
    QColorDialog colourDialog;
    QPen myPen;
    QBrush myBrush;

    QString fileName = "testMyfile.png";



    QGraphicsItem *figure=nullptr;





public:
    MyScene(QObject *parent=nullptr);

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

        void saveOption();

        void clearScene();





protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;
};

#endif // MYSCENE_H














