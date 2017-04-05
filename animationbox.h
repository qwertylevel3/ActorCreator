#ifndef ANIMATIONBOX_H
#define ANIMATIONBOX_H

#include"animation.h"
#include<QDomDocument>

class AnimationBox
{
public:
    AnimationBox();
    bool init(const QString& fileName);
    QList<Animation> &getAllAnimationRef();
protected:
    bool readAnimation(QDomElement& node);
    void initAnimationFrame(AnimationFrame &frame,QDomElement& element);
    void readRect(QRect &rect,QDomElement& element);
    QList<Animation> allAnimation;
};

#endif // ANIMATIONBOX_H
