#include "rectobject.h"
#include"rectdialog.h"

using namespace std;

RectObject::RectObject()
{
    setFlag(QGraphicsItem::ItemIsMovable,true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    rect=QRectF(0,0,50,50);
}

QRectF RectObject::boundingRect() const
{
    return rect;
}

void RectObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setOpacity(0.5);
    painter->setBrush(QBrush(color,Qt::SolidPattern));
    painter->drawRect(rect);
    //painter->fillRect(rect,brush);
}

void RectObject::setRect(QRectF r)
{
    rect=r;
    update();
}

QRectF RectObject::getRect()
{
    return rect;
}

void RectObject::setRectColor(QColor c)
{
    color=c;
}

void RectObject::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    RectDialog dialog(nullptr,this);
    if(dialog.exec())
    {
        return;
    }
}


