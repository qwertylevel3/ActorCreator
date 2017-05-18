#ifndef ANIMATIONBOX_H
#define ANIMATIONBOX_H

#include"animation.h"
#include"stable.h"

class AnimationBox:public QStandardItem
{
public:
    AnimationBox();
    bool init(const QString& fileName);
    bool save(const QString& fileName);
    void clear();
    void addAnimation(Animation* a);
protected:
    bool readAnimation(QDomElement& node);
    void initAnimationFrame(AnimationFrame* frame,QDomElement& element);
    void readRect(AnimationFrameRect* rect,QDomElement& element);

    void saveAnimation(QDomDocument& doc,QDomElement& node,Animation* animation);
    void saveRect(QDomDocument& doc,QDomElement& node,AnimationFrameRect* animationFrameRect);

    QString curFile;
    QString resourceDir;
};

#endif // ANIMATIONBOX_H
