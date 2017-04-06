#include "animationbox.h"

AnimationBox::AnimationBox()
{

}

bool AnimationBox::init(const QString &fileName)
{
    clear();

    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        std::cerr<<fileName.toStdString()<<" can not open"<<std::endl;
        return false;
    }

    QDomDocument doc;
    QString errorStr;
    int errorLine;
    int errorColumn;
    if(!doc.setContent(&file,false,&errorStr,&errorLine,&errorColumn))
    {
        std::cerr<<"error: parse error at line"<<errorLine<<","
                <<"column "<<errorColumn<<":"
               <<qPrintable(errorStr)<<std::endl;
        return false;
    }

    QDomElement animationBoxElement=doc.documentElement();

    QDomElement animationElement=animationBoxElement.firstChildElement();
    while(!animationElement.isNull())
    {
        readAnimation(animationElement);
        animationElement=animationElement.nextSiblingElement();
    }
    return true;
}

QList<Animation> &AnimationBox::getAllAnimationRef()
{
    return allAnimation;
}

void AnimationBox::clear()
{
    allAnimation.clear();
}

bool AnimationBox::readAnimation(QDomElement& node)
{
    Animation animation;

    //ID
    QDomElement idElement=node.firstChildElement();
    animation.id=idElement.text();

    QDomElement frameElement=idElement.nextSiblingElement();

    while(!frameElement.isNull())
    {
        //frame
        AnimationFrame frame;
        initAnimationFrame(frame,frameElement);
        animation.addFrame(frame);

        frameElement=frameElement.nextSiblingElement();
    }

    allAnimation.push_back(animation);

    return true;
}

void AnimationBox::initAnimationFrame(AnimationFrame &frame,QDomElement& element)
{
    //sprite
    QDomElement attrElement=element.firstChildElement();
    QString spriteFrame=attrElement.text();
    frame.sprite=spriteFrame;

    //delayUnits
    attrElement=attrElement.nextSiblingElement();
    float delayUnits=attrElement.text().toFloat();
    frame.delayUnits=delayUnits;

    //atkRect
    attrElement=attrElement.nextSiblingElement();
    QDomElement rectElement=attrElement.firstChildElement();
    while(!rectElement.isNull())
    {
        QRect rect;
        readRect(rect,rectElement);
        frame.addAtkRect(rect);

        rectElement=rectElement.nextSiblingElement();
    }

    //bodyRect
    attrElement=attrElement.nextSiblingElement();
    rectElement=attrElement.firstChildElement();
    while(!rectElement.isNull())
    {
        QRect rect;
        readRect(rect,rectElement);
        frame.addAtkRect(rect);
        rectElement=rectElement.nextSiblingElement();
    }

    //phyRect
    attrElement=attrElement.nextSiblingElement();
    rectElement=attrElement.firstChildElement();
    while(!rectElement.isNull())
    {
        QRect rect;
        readRect(rect,rectElement);
        frame.addAtkRect(rect);
        rectElement=rectElement.nextSiblingElement();
    }
}

void AnimationBox::readRect(QRect &rect,QDomElement& element)
{
    //x
    QDomElement attrElement=element.firstChildElement();
    rect.setX(attrElement.text().toInt());

    //y
    attrElement=attrElement.nextSiblingElement();
    rect.setY(attrElement.text().toInt());

    //w
    attrElement=attrElement.nextSiblingElement();
    rect.setWidth(attrElement.text().toInt());

    //h
    attrElement=attrElement.nextSiblingElement();
    rect.setHeight(attrElement.text().toInt());

}
