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
    void setSpriteName(const QString& s);
    void setDelayUnits(float d);
    QString getSpriteName();
    float getDelayUnits();

    QString getSpritePath();
    void setSpritePath(const QString& path);
protected:
    QString spriteName;
    QString spritePath;
    float delayUnits;
};



#endif // ANIMATIONFRAME_H
