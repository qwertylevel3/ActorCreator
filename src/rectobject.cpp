#include "rectobject.h"
#include"rectdialog.h"
#include"animationframerect.h"

using namespace std;

RectObject::RectObject(AnimationFrameRect* r)
    :rectPtr(r)
{
    setFlag(QGraphicsItem::ItemIsMovable,true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setRect(rectPtr->getRect());
    rectPtr->object=this;
}

void RectObject::setRectColor(QColor c)
{
    color=c;
}

void RectObject::setRectWidth(int w)
{
    rectPtr->setWidth(w);
    this->setRect(rectPtr->getRect());
}

void RectObject::setRectHeight(int h)
{
    rectPtr->setHeight(h);
    this->setRect(rectPtr->getRect());
}

void RectObject::setParentItem(QGraphicsItem *parent)
{
    QGraphicsRectItem::setParentItem(parent);
}

void RectObject::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    RectDialog dialog(nullptr,this);
    if(dialog.exec())
    {
        return;
    }
    this->setRect(rectPtr->getRect());
}

void RectObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsRectItem::mousePressEvent(event);
    startPos=event->pos();
    startPos=mapToScene(startPos);
}


void RectObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsRectItem::mouseReleaseEvent(event);
}

void RectObject::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF endPos=event->pos();
    endPos=mapToScene(endPos);
    QPointF dis=endPos-startPos;
    startPos=endPos;
    rectPtr->moveBy(dis);
    this->setRect(rectPtr->getRect());
}


