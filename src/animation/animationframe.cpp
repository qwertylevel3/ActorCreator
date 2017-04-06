#include "animationframe.h"

AnimationFrame::AnimationFrame()
{
//    this->setRowCount(3);
    this->appendRow(new AnimationFrameRect);
    this->appendRow(new AnimationFrameRect);
    this->appendRow(new AnimationFrameRect);
}

void AnimationFrame::addAtkRect(AnimationFrameRect* rect)
{
    this->child(ATKRECT)->appendRow(rect);
}

void AnimationFrame::addBodyRect(AnimationFrameRect* rect)
{
    this->child(BODYRECT)->appendRow(rect);
}

void AnimationFrame::addPhyRect(AnimationFrameRect *rect)
{
    this->child(PHYRECT)->appendRow(rect);
}

void AnimationFrame::setSprite(const QString &s)
{
    sprite=s;
}

void AnimationFrame::setDelayUnits(float d)
{
    delayUnits=d;
}

QString AnimationFrame::getSprite()
{
    return sprite;
}

float AnimationFrame::getDelayUnits()
{
    return delayUnits;
}

