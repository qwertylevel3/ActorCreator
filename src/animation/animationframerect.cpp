#include "animationframerect.h"

AnimationFrameRect::AnimationFrameRect()
{

}

void AnimationFrameRect::setX(int x)
{
    rect.setX(x);
    updateText();
}

void AnimationFrameRect::setY(int y)
{
    rect.setY(y);
    updateText();
}

void AnimationFrameRect::setWidth(int w)
{
    rect.setWidth(w);
    updateText();
}

void AnimationFrameRect::setHeight(int h)
{
    rect.setHeight(h);
    updateText();
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

void AnimationFrameRect::updateText()
{
    QString text=QString::number(rect.x())+QString("|")
            +QString::number(rect.y())+QString("|")
            +QString::number(rect.width())+QString("|")
            +QString::number(rect.height());
    this->setText(text);
}

void AnimationFrameRect::setRect(QRect r)
{
    this->rect=r;
    updateText();
}
