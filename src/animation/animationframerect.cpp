#include "animationframerect.h"

AnimationFrameRect::AnimationFrameRect()
{

}

void AnimationFrameRect::setX(int x)
{
    rect.setX(x);
}

void AnimationFrameRect::setY(int y)
{
    rect.setY(y);
}

void AnimationFrameRect::setWidth(int w)
{
    rect.setWidth(w);
}

void AnimationFrameRect::setHeight(int h)
{
    rect.setHeight(h);
}

int AnimationFrameRect::getX()
{
    return rect.x();
}

int AnimationFrameRect::getY()
{
    return rect.y();
}

int AnimationFrameRect::getWidth()
{
    return rect.width();
}

int AnimationFrameRect::getHeight()
{
    return rect.height();
}
