#include "animationframe.h"

void AnimationFrame::addAtkRect(QRect rect)
{
    atkRectBox.push_back(rect);
}

void AnimationFrame::addBodyRect(QRect rect)
{
    bodyRectBox.push_back(rect);
}

void AnimationFrame::addPhyRect(QRect rect)
{
    phyRectBox.push_back(rect);
}

