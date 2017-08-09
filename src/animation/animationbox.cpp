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

    curFile=fileName;
    resourceDir=curFile.left(curFile.lastIndexOf('/'))+"/resource/";


    this->setText(fileName);

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

bool AnimationBox::save(const QString &fileName)
{

    QDomDocument doc;
//    QString errorStr;
//    int errorLine;
//    int errorColumn;
//    if(!doc.setContent(&file,false,&errorStr,&errorLine,&errorColumn))
//    {
//        std::cerr<<"error: parse error at line"<<errorLine<<","
//                <<"column "<<errorColumn<<":"
//               <<qPrintable(errorStr)<<std::endl;
//        return false;
//    }

    QDomElement animationBoxElement=doc.createElement("animationBox");
    doc.appendChild(animationBoxElement);

    for(int i=0;i<this->rowCount();i++)
    {
        Animation* animation=static_cast<Animation*>(this->child(i));
        saveAnimation(doc,animationBoxElement,animation);
    }
    QString docStr=doc.toString();
    QFile file(fileName);

    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        std::cerr<<fileName.toStdString()<<" can not open"<<std::endl;
        return false;
    }
    QTextStream txtOutput(&file);
    txtOutput<<docStr<<endl;

    return true;
}


void AnimationBox::clear()
{
    int count=this->rowCount();
    for(int i=0;i<count;i++)
    {
        this->removeRow(0);
    }
}

void AnimationBox::addAnimation(Animation *a)
{
    this->appendRow(a);
}

bool AnimationBox::readAnimation(QDomElement& node)
{
    Animation* animation=new Animation();

    //ID
    QDomElement idElement=node.firstChildElement();
    animation->setID(idElement.text());

    QDomElement frameElement=idElement.nextSiblingElement();

    while(!frameElement.isNull())
    {
        //frame
        AnimationFrame* frame=new AnimationFrame;
        initAnimationFrame(frame,frameElement);
        animation->addFrame(frame);

        frameElement=frameElement.nextSiblingElement();
    }

    this->addAnimation(animation);

    return true;
}

void AnimationBox::initAnimationFrame(AnimationFrame* frame,QDomElement& element)
{
    //sprite
    QDomElement attrElement=element.firstChildElement();
    QString spriteName=attrElement.text();
    spriteName=resourceDir+spriteName;
    frame->setSpriteName(spriteName);

    //path
//    attrElement=attrElement.nextSiblingElement();
//    QString spritePath=attrElement.text();
//    spritePath=resourceDir+spritePath;
//    frame->setSpritePath(spritePath);

    //delayUnits
    attrElement=attrElement.nextSiblingElement();
    float delayUnits=attrElement.text().toFloat();
    frame->setDelayUnits(delayUnits);

    //atkRect
    attrElement=attrElement.nextSiblingElement();
    QDomElement rectElement=attrElement.firstChildElement();
    while(!rectElement.isNull())
    {
        AnimationFrameRect* rect=new AnimationFrameRect();
        readRect(rect,rectElement);
        frame->addAtkRect(rect);
        rectElement=rectElement.nextSiblingElement();
    }

    //bodyRect
    attrElement=attrElement.nextSiblingElement();
    rectElement=attrElement.firstChildElement();
    while(!rectElement.isNull())
    {
        AnimationFrameRect* rect=new AnimationFrameRect();
        readRect(rect,rectElement);
        frame->addBodyRect(rect);
        rectElement=rectElement.nextSiblingElement();
    }

    //phyRect
    attrElement=attrElement.nextSiblingElement();
    rectElement=attrElement.firstChildElement();
    while(!rectElement.isNull())
    {
        AnimationFrameRect* rect=new AnimationFrameRect();
        readRect(rect,rectElement);
        frame->addPhyRect(rect);
        rectElement=rectElement.nextSiblingElement();
    }
}

void AnimationBox::readRect(AnimationFrameRect* rect,QDomElement& element)
{
    //x
    QDomElement attrElement=element.firstChildElement();
    int x=attrElement.text().toInt();

    //y
    attrElement=attrElement.nextSiblingElement();
    int y=attrElement.text().toInt();

    //w
    attrElement=attrElement.nextSiblingElement();
    int w=attrElement.text().toInt();

    //h
    attrElement=attrElement.nextSiblingElement();
    int h=attrElement.text().toInt();

    rect->setX(x);
    rect->setY(-y-h);
    rect->setWidth(w);
    rect->setHeight(h);
}

void AnimationBox::saveAnimation(QDomDocument& doc,QDomElement &node, Animation *animation)
{
    QDomElement animationElement=doc.createElement("animation");
    node.appendChild(animationElement);

    QDomElement idElement=doc.createElement("ID");
    animationElement.appendChild(idElement);
    QString id=animation->getID();
    QDomText idText=doc.createTextNode(id);
    idElement.appendChild(idText);


    for(int i=0;i<animation->rowCount();i++)
    {
        QDomElement frameElement=doc.createElement("frame");
        animationElement.appendChild(frameElement);

        AnimationFrame* animationFrame=static_cast<AnimationFrame*>(animation->child(i));

        QDomElement spriteFrameElement=doc.createElement("spriteFrame");
        frameElement.appendChild(spriteFrameElement);
        //只写入png文件名,不写入路径
        QString picPath=animationFrame->getSpriteName();
        int index=picPath.lastIndexOf("/");
        picPath=picPath.mid(index+1);
        QDomText spriteFrameText=doc.createTextNode(picPath);
        spriteFrameElement.appendChild(spriteFrameText);

        QDomElement delayUnitsElement=doc.createElement("delayUnits");
        frameElement.appendChild(delayUnitsElement);
        QDomText delayUnitsText=doc.createTextNode(QString::number(animationFrame->getDelayUnits()));
        delayUnitsElement.appendChild(delayUnitsText);

        QDomElement atkBoxElement=doc.createElement("atkRectBox");
        frameElement.appendChild(atkBoxElement);
        QStandardItem* atkBox=animationFrame->child(0);
        for(int i=0;i<atkBox->rowCount();i++)
        {
            AnimationFrameRect* animationFrameRect=
                    static_cast<AnimationFrameRect*>(atkBox->child(i));
            saveRect(doc,atkBoxElement,animationFrameRect);
        }
        QDomElement bodyBoxElement=doc.createElement("bodyRectBox");
        frameElement.appendChild(bodyBoxElement);
        QStandardItem* bodyBox=animationFrame->child(1);
        for(int i=0;i<bodyBox->rowCount();i++)
        {
            AnimationFrameRect* animationFrameRect=
                    static_cast<AnimationFrameRect*>(bodyBox->child(i));
            saveRect(doc,bodyBoxElement,animationFrameRect);
        }

        QDomElement phyBoxElement=doc.createElement("phyRectBox");
        frameElement.appendChild(phyBoxElement);
        QStandardItem* phyBox=animationFrame->child(2);
        for(int i=0;i<phyBox->rowCount();i++)
        {
            AnimationFrameRect* animationFrameRect=
                    static_cast<AnimationFrameRect*>(phyBox->child(i));
            saveRect(doc,phyBoxElement,animationFrameRect);
        }
    }
}

void AnimationBox::saveRect(QDomDocument &doc, QDomElement &node, AnimationFrameRect *animationFrameRect)
{
    QDomElement rectElement=doc.createElement("rect");
    node.appendChild(rectElement);

    int x=animationFrameRect->getX();
    int y=animationFrameRect->getY();
    int w=animationFrameRect->getWidth();
    int h=animationFrameRect->getHeight();

    QDomElement xElement=doc.createElement("x");
    rectElement.appendChild(xElement);
    QDomText xText=doc.createTextNode(QString::number(x));
    xElement.appendChild(xText);

    QDomElement yElement=doc.createElement("y");
    rectElement.appendChild(yElement);
    QDomText yText=doc.createTextNode(QString::number(-y-h));
    yElement.appendChild(yText);

    QDomElement wElement=doc.createElement("w");
    rectElement.appendChild(wElement);
    QDomText wText=doc.createTextNode(QString::number(w));
    wElement.appendChild(wText);

    QDomElement hElement=doc.createElement("h");
    rectElement.appendChild(hElement);
    QDomText hText=doc.createTextNode(QString::number(h));
    hElement.appendChild(hText);
}
