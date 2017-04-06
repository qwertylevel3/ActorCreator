#ifndef ANIMATION_H
#define ANIMATION_H


#include"animationframe.h"

struct Animation
{
    void addFrame(AnimationFrame f);
    QList<AnimationFrame> frameList;
    QString id;
};

#endif // ANIMATION_H
