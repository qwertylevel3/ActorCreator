#include "rect.h"

Rect::Rect()
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

QRectF Rect::boundingRect() const
{
     return QRectF(-30, -20, 60, 60);
}

void Rect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawRect(-30,-20,60,60);
}
