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
 this->setDefaultTextColor(myColor);
 this->setFlag(QGraphicsItem::ItemIsSelectable,true);
 this->setFlag ( QGraphicsItem::ItemIsMovable,true);
 this->setFlag(QGraphicsItem::ItemIsFocusable,true);
 this->setTextInteractionFlags(Qt::TextEditorInteraction);
 this->setFlag(QGraphicsItem::ItemAcceptsInputMethod);



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

