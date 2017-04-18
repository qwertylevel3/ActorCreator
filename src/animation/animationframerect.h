#ifndef ANIMATIONFRAMERECT_H
#define ANIMATIONFRAMERECT_H


#include"stable.h"

class RectObject;


class AnimationFrameRect:public QStandardItem
{
    friend class RectObject;
public:
    AnimationFrameRect();

    void setWidth(int w);
    void setHeight(int h);
    void setX(int x);
    void setY(int y);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void setRect(QRectF r);
    QRectF getRect();
    void moveBy(QPointF dis);

    void updateText();
    void selectObject();
protected:
    QRectF rect;
    RectObject* object;
};

#endif // ANIMATIONFRAMERECT_H
