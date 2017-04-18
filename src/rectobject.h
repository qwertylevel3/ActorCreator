#ifndef RECTOBJECT_H
#define RECTOBJECT_H

#include"stable.h"


class AnimationFrameRect;


class RectObject:public QGraphicsRectItem
{
public:
    RectObject(AnimationFrameRect* r);
    void setRectColor(QColor c);
    void setRectWidth(int w);
    void setRectHeight(int h);
    void setParentItem(QGraphicsItem *parent);
//TODO
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
protected:
    void save();
    QPointF startPos;
    QColor color;
    AnimationFrameRect* rectPtr;
};

#endif // RECTOBJECT_H
