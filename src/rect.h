#ifndef RECT_H
#define RECT_H

#include"stable.h"


class Rect:public QGraphicsObject
{
public:
    Rect();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) Q_DECL_OVERRIDE;
};

#endif // RECT_H
