#include "animation.h"


Animation::Animation()
{

}

void Animation::addFrame(AnimationFrame *f)
{
    this->appendRow(f);
}

void Animation::setID(const QString &i)
{
    id=i;
}

QString Animation::getID()
{
    return id;
}
