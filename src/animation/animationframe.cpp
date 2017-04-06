#include "animationframe.h"

AnimationFrame *AnimationFrame::clone() const
{
    AnimationFrame* newFrame=new AnimationFrame();

    for(int i=0;i<this->rowCount();i++)
    {
        for(int j=0;j<this->child(i)->rowCount();j++)
        {
            newFrame->child(i)->appendRow(
                        this->child(i)->child(j)->clone()
                        );
        }
    }
    newFrame->setSprite(this->sprite);
    newFrame->setDelayUnits(this->delayUnits);
    return newFrame;
}

AnimationFrame::AnimationFrame()
{
    QStandardItem* atkBox=new QStandardItem();
    atkBox->setText("atk");
    QStandardItem* bodyBox=new QStandardItem();
    bodyBox->setText("body");
    QStandardItem* phyBox=new QStandardItem();
    phyBox->setText("phy");

    this->appendRow(atkBox);
    this->appendRow(bodyBox);
    this->appendRow(phyBox);
}

void AnimationFrame::addAtkRect(AnimationFrameRect* rect)
{
    this->child(ATKRECT)->appendRow(rect);
}

void AnimationFrame::addBodyRect(AnimationFrameRect* rect)
{
    this->child(BODYRECT)->appendRow(rect);
}

void AnimationFrame::addPhyRect(AnimationFrameRect *rect)
{
    this->child(PHYRECT)->appendRow(rect);
}

void AnimationFrame::setSprite(const QString &s)
{
    sprite=s;
    this->setText(sprite);
}

void AnimationFrame::setDelayUnits(float d)
{
    delayUnits=d;
}

QString AnimationFrame::getSprite()
{
    return sprite;
}

float AnimationFrame::getDelayUnits()
{
    return delayUnits;
}

