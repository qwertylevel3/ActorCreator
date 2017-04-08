#ifndef ANIMATIONFRAMERECT_H
#define ANIMATIONFRAMERECT_H


#include"stable.h"

class AnimationFrameRect:public QStandardItem
{
public:
    AnimationFrameRect();

    void setX(int x);
    void setY(int y);
    void setWidth(int w);
    void setHeight(int h);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void setRect(QRect r);
    QRect getRect();

    void updateText();
protected:
    QRect rect;
};

#endif // ANIMATIONFRAMERECT_H
