#ifndef ANIMATIONFRAME_H
#define ANIMATIONFRAME_H

#include"stable.h"

#include"animationframerect.h"

class AnimationFrame:public QStandardItem
{
public:
    enum RectType
    {
        ATKRECT,BODYRECT,PHYRECT
    };

    AnimationFrame();
    void addAtkRect(AnimationFrameRect* rect);
    void addBodyRect(AnimationFrameRect* rect);
    void addPhyRect(AnimationFrameRect* rect);
    void setSprite(const QString& s);
    void setDelayUnits(float d);
    QString getSprite();
    float getDelayUnits();
protected:
    QString sprite;
    float delayUnits;
};

#endif // ANIMATIONFRAME_H
