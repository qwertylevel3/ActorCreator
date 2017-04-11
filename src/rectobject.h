#ifndef RECTOBJECT_H
#define RECTOBJECT_H

#include"stable.h"


class RectObject:public QGraphicsObject
{
public:
    RectObject();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) Q_DECL_OVERRIDE;
    void setRect(QRectF r);
    QRectF getRect();
    void setRectColor(QColor c);
//TODO
//    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
protected:
    QRectF rect;
    QPointF startPos;
    QColor color;
};

#endif // RECTOBJECT_H
