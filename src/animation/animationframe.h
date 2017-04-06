#ifndef ANIMATIONFRAME_H
#define ANIMATIONFRAME_H

#include"stable.h"

struct AnimationFrame
{
    void addAtkRect(QRect rect);
    void addBodyRect(QRect rect);
    void addPhyRect(QRect rect);
    QString sprite;
    float delayUnits;
    QList<QRect> atkRectBox;
    QList<QRect> bodyRectBox;
    QList<QRect> phyRectBox;
};

#endif // ANIMATIONFRAME_H
