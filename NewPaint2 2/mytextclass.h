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

    QColor myColor=Qt::red;
    QFont myFont;

    QPointF myPoint;

    const QString warnTextMessage={"No Text object"};


public:
     MyTextClass( QGraphicsItem *parent=nullptr);
     virtual ~MyTextClass()=default;
     void setTextColor (QColor myTextColour);




signals:
    void lostFocus(MyTextClass *myText);
    void selectedChange(QGraphicsItem *item);



// QGraphicsItem interface
protected:
     QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
     void focusOutEvent(QFocusEvent *event) override;
     void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
     void focusInEvent(QFocusEvent *event) override;





};



#endif // MYTEXTCLASS_H
