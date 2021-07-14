#include "mytextclass.h"
#include <figuretype.h>
#include <QPainter>
#include <QColorDialog>
#include<QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include<QInputDialog>


MyTextClass::MyTextClass(QGraphicsItem *parent ):  QGraphicsTextItem(parent)
{


 myFont=(QFont("Courier"));
 myColor=Qt::green;
 setDefaultTextColor(myColor);
setFlag(QGraphicsItem::ItemIsSelectable,true);
 setFlag ( QGraphicsItem::ItemIsMovable,true);
 setFlag(QGraphicsItem::ItemIsFocusable,true);
  //setTextInteractionFlags(Qt::TextEditorInteraction);



}



void MyTextClass::focusOutEvent(QFocusEvent *event)
{

   this-> setTextInteractionFlags(Qt::NoTextInteraction);

    this->clearFocus();
     emit lostFocus(this);
    QGraphicsTextItem::focusOutEvent(event);
}

void MyTextClass::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<Q_FUNC_INFO;
    if (textInteractionFlags() == Qt::NoTextInteraction)
            setTextInteractionFlags(Qt::TextEditorInteraction);
   // setFocus();
    QGraphicsTextItem::mouseDoubleClickEvent(event);
}


QVariant MyTextClass::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged)
        emit selectedChange(this);
    return value;
}

