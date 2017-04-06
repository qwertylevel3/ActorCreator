#ifndef ANIMATION_H
#define ANIMATION_H


#include"stable.h"

#include"animationframe.h"


class Animation:public QStandardItem
{
public:
    Animation();
    void addFrame(AnimationFrame* f);
    void setID(const QString& i);
    QString getID();
protected:
    QString id;
};

#endif // ANIMATION_H
