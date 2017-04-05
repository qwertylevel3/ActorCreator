#include "animation.h"
#include<QXmlStreamReader>


void Animation::addFrame(AnimationFrame f)
{
    frameList.push_back(f);
}
