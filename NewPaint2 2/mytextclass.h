#ifndef MYTEXTCLASS_H
#define MYTEXTCLASS_H

#include <QGraphicsTextItem>
#include<QMessageBox>
#include<QGraphicsScene>


class MyTextClass : public QGraphicsTextItem
{
   Q_OBJECT

    QList<QGraphicsTextItem*> textContainer;
    QGraphicsTextItem *myTextItem;
    QMessageBox *messBox;

    QColor myColor;
    QFont myFont;

    QPointF myPoint;
   //QString myItemString_;

    const QString warnTextMessage={"No Text object"};


public:
     MyTextClass( QGraphicsItem *parent=nullptr);

    virtual ~MyTextClass()=default;




public:
//virtual QRectF boundingRect() const override;
//virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

signals:
    void lostFocus(MyTextClass *myText);
    void selectedChange(QGraphicsItem *item);

// QGraphicsItem interface
protected:
  QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
  void focusOutEvent(QFocusEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;


};



#endif // MYTEXTCLASS_H
