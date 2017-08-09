#include "animation.h"


Animation::Animation()
{

}

void Animation::addFrame(AnimationFrame *f)
{
    this->appendRow(f);
}

void Animation::addFrame(const QString &picFileName)
{
    AnimationFrame* frame=new AnimationFrame();
    frame->setSpriteName(picFileName);
    frame->setDelayUnits(1);

    addFrame(frame);
}

void Animation::setID(const QString &i)
{
    id=i;
    this->setText(id);
}

QString Animation::getID()
{
    return id;
}
