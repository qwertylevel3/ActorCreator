#ifndef ANIMATIONFRAMERECT_H
#define ANIMATIONFRAMERECT_H


#include"stable.h"


class AnimationFrameRect:public QStandardItem
{
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
//    void deleteSelf();
protected:
    QRectF rect;
};

#endif // ANIMATIONFRAMERECT_H
