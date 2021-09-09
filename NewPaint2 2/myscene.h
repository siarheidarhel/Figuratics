#ifndef MYSCENE_H
#define MYSCENE_H

#include <figuretype.h>
#include <mytextclass.h>

#include <QBrush>
#include <QColor>
#include <QColorDialog>
#include <QFile>
#include <QFileDialog>
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QListWidget>
#include <QMessageBox>
#include <QPen>
#include <QPointF>
#include <QStack>
#include <QString>

class MyScene : public QGraphicsScene {
  Q_OBJECT
  QGraphicsTextItem *myTextItem;

  int figureType_ = 0;

  const QString warnMessage = {"No UNDO availible"};
  //    const QString warnTextMessage={"No Text object"};
  QPointF start_point;
  QPointF end_point;
  QMessageBox messBox;

  QStack<QGraphicsItem *> saveContainer_;
  QList<QGraphicsItemGroup *> savePancil;
  QGraphicsItemGroup myGroup;

  QColorDialog colourDialog;
  QFont myFont;
  QPen myPen;
  QBrush myBrush;
  int myRotate = 0;
  float myOpacity = 1.0;

  int myAt = 0;

  int myChangeZValue = 0;
  int myStrartZValue = 0;

  QString fileName = "testMyfile.png";

  QGraphicsItem *figure = nullptr;

 public:
  explicit MyScene(QObject *parent = nullptr);
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

  void clearScene();
  void rotationFigure(int rotate);
  void scaleFigure(int scale);

  void myOpacityFunc(float opacity);

  void bringToFront();
  void bringToBack();

 public slots:
  void editorLostFocus(MyTextClass *myText);

 signals:
  void itemSelected(QGraphicsItem *item);
  void myReset();
  void signalListWidget();

 protected:
  virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
  virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
  virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif  // MYSCENE_H
