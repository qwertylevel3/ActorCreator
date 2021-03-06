#include "animationframe.h"

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

    this->setEditable(false);

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

void AnimationFrame::setSpriteName(const QString &s)
{
    spriteName=s;
    //this->setText(sprite);
//    this->setEditable(false);

    QPixmap iconPixmap(s);
    QIcon icon(iconPixmap);
    this->setSizeHint(iconPixmap.size());
    this->setIcon(icon);
}

void AnimationFrame::setDelayUnits(float d)
{
    delayUnits=d;
}

QString AnimationFrame::getSpriteName()
{
    return spriteName;
}

float AnimationFrame::getDelayUnits()
{
    return delayUnits;
}

QString AnimationFrame::getSpritePath()
{
    return spritePath;
}

void AnimationFrame::setSpritePath(const QString &path)
{
    spritePath=path;
}

