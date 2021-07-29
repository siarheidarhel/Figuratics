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
 myColor=Qt::black;
 this->setDefaultTextColor(myColor);
 this->setFlag(QGraphicsItem::ItemIsSelectable,true);
 this->setFlag ( QGraphicsItem::ItemIsMovable,true);
 this->setFlag(QGraphicsItem::ItemIsFocusable,true);
 this->setTextInteractionFlags(Qt::TextEditorInteraction);
 this->setFlag(QGraphicsItem::ItemAcceptsInputMethod);
 this->setFocus(Qt::MouseFocusReason);





}

void MyTextClass::setTextColor(QColor myTextColour)
{
     myColor=myTextColour;
}




void MyTextClass::focusOutEvent(QFocusEvent *event)
{

   this-> setTextInteractionFlags(Qt::NoTextInteraction);

    //this->clearFocus();
     emit lostFocus(this);

    QGraphicsTextItem::focusOutEvent(event);
}

void MyTextClass::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<Q_FUNC_INFO;

    if (textInteractionFlags() == Qt::NoTextInteraction)
            setTextInteractionFlags(Qt::TextEditorInteraction);

    QGraphicsTextItem::mouseDoubleClickEvent(event);
}

//QRectF MyTextClass::boundingRect() const
//{
//     QRectF myRect= myTextItem->boundingRect();
//    return myRect;
//}

void MyTextClass::focusInEvent(QFocusEvent *event)
{
    qDebug()<<Q_FUNC_INFO;
    this->setFocus(Qt::MouseFocusReason);


    QGraphicsTextItem::focusInEvent(event);
}


QVariant MyTextClass::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged)
        emit selectedChange(this);
    return value;
}

