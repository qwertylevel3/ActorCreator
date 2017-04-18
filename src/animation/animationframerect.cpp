#include "animationframerect.h"
#include"rectobject.h"


AnimationFrameRect::AnimationFrameRect()
{
    this->setEditable(false);
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

void AnimationFrameRect::setX(int x)
{
//    rect.translate(x,rect.y());
    rect.setX(x);
    updateText();
}

void AnimationFrameRect::setY(int y)
{
//    rect.translate(rect.x(),y);
    rect.setY(y);
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
            +QString::number(-rect.y()-rect.height())+QString("|")
            +QString::number(rect.width())+QString("|")
            +QString::number(rect.height());
    this->setText(text);
}

void AnimationFrameRect::selectObject()
{
    object->setSelected(true);
}


void AnimationFrameRect::setRect(QRectF r)
{
    this->rect=r;
    updateText();
}


QRectF AnimationFrameRect::getRect()
{
    return rect;
}

void AnimationFrameRect::moveBy(QPointF dis)
{
    rect.moveTo(rect.x()+dis.x(),rect.y()+dis.y());
}
