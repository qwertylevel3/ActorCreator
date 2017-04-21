#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"animationbox.h"
#include"rectobject.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    modified=false;

    ui->setupUi(this);

    connectActions();


    model=nullptr;

    view=new QGraphicsView(this);
    scene=new QGraphicsScene(this);

    ui->spriteDockWidget->setWidget(view);
    view->setScene(scene);
    view->setAcceptDrops(true);

    ui->animationDockWidget->setEnabled(false);
    ui->frameDockWidget->setEnabled(false);
    ui->rectDockWidget->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
}


void MainWindow::openFileSlot()
{
    curFile=QFileDialog::getOpenFileName(this,
                                         tr("Open animation file"),".",
                                         tr("animation file(*.xml)"));
    open(curFile);
    modified=true;
}

void MainWindow::newFileSlot()
{
    //TODO
    model=new QStandardItemModel();
    animationBox=new AnimationBox;
    model->appendRow(animationBox);

    updateAnimationView();
}

void MainWindow::saveFileSlot()
{
    if(!curFile.isEmpty())
    {
        animationBox->save(curFile);
    }
    else
    {
        curFile=QFileDialog::getSaveFileName(
                                this,
                                tr("save animation file"),".",
                                tr("animation file(*.xml)")
                                );
        animationBox->save(curFile);
    }
}

bool MainWindow::closeFileSlot()
{
    bool flag=false;
    if(isModified())
    {
        int choose=QMessageBox::warning(
                                this,
                                tr("warning"),
                                tr("save?"),
                                QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel
                                );
        if(choose==QMessageBox::Yes)
        {
            saveFileSlot();
            closeFile();
            flag=true;
        }
        else if(choose==QMessageBox::No)
        {
            closeFile();
            flag=true;
        }
        else if(choose==QMessageBox::Cancel)
        {
            flag=false;
        }
    }
    else
    {
        closeFile();
        flag=true;
    }
    modified=false;
    return true;
}


void MainWindow::updateRectView()
{
    if(!model)
    {
        return;
    }

    curFrameIndex=ui->frameView->currentIndex();

    if(curFrameIndex.child(0,0).isValid())
    {
        QModelIndex atkRootIndex=curFrameIndex.child(0,0);
        ui->atkRectView->setModel(model);
        ui->atkRectView->setRootIndex(atkRootIndex);
    }

    if(curFrameIndex.child(1,0).isValid())
    {
        QModelIndex bodyRootIndex=curFrameIndex.child(1,0);
        ui->bodyRectView->setModel(model);
        ui->bodyRectView->setRootIndex(bodyRootIndex);
    }

    if(curFrameIndex.child(2,0).isValid())
    {
        QModelIndex phyRootIndex=curFrameIndex.child(2,0);
        ui->phyRectView->setModel(model);
        ui->phyRectView->setRootIndex(phyRootIndex);
    }

    updateScene();
}

void MainWindow::updateFrameView()
{
    if(!model)
    {
        return;
    }

    curAnimationIndex=ui->animationView->currentIndex();
    ui->frameView->setModel(model);
    ui->frameView->setRootIndex(curAnimationIndex);

    if(curAnimationIndex.child(0,0).isValid())
    {
        //当前animation有一个以上的frame
        curFrameIndex=curAnimationIndex.child(0,0);
        ui->frameView->setCurrentIndex(curFrameIndex);
        updateRectView();
        ui->rectDockWidget->setEnabled(true);
    }
    else
    {
        //如果当前animation没有frame设置各个view为空
        ui->rectDockWidget->setEnabled(false);
        ui->atkRectView->setModel(nullptr);
        ui->bodyRectView->setModel(nullptr);
        ui->phyRectView->setModel(nullptr);
        ui->frameView->setModel(nullptr);
    }

}

void MainWindow::updateAnimationView()
{
    if(!model)
    {
        return;
    }
    scene->clear();

    ui->animationDockWidget->setEnabled(true);
    ui->animationView->setModel(model);
    ui->animationView->setRootIndex(animationBox->index());
    curAnimationIndex=ui->animationView->currentIndex();

    if(curAnimationIndex.isValid())
    {
        //当前animatoinBox不为空
        ui->frameDockWidget->setEnabled(true);
        updateFrameView();
    }
    else
    {
        ui->rectDockWidget->setEnabled(false);
        ui->frameDockWidget->setEnabled(false);
        ui->atkRectView->setModel(nullptr);
        ui->bodyRectView->setModel(nullptr);
        ui->phyRectView->setModel(nullptr);
        ui->frameView->setModel(nullptr);
    }
}

void MainWindow::updateScene()
{
    scene->clear();

    showSprite();
    showRect();

    scene->update();
    view->update();
}

void MainWindow::changeRectTab(int index)
{
    scene->clear();
    if(!model)
    {
        return;
    }
    showSprite();
    showRect();
}

void MainWindow::addAtkRect()
{
    if(!model  )
    {
        return;
    }
    //    QModelIndex atkRootIndex=curFrameIndex.child(0,0);

    AnimationFrame* curFrame=static_cast<AnimationFrame*>(model->itemFromIndex(curFrameIndex));

    AnimationFrameRect* atkRect=new AnimationFrameRect();

    atkRect->setWidth(20);
    atkRect->setHeight(20);
    atkRect->setX(0);
    atkRect->setY(0);

    curFrame->addAtkRect(atkRect);
    updateScene();
}

void MainWindow::addBodyRect()
{
    if(!model  )
    {
        return;
    }

    AnimationFrame* curFrame=static_cast<AnimationFrame*>(model->itemFromIndex(curFrameIndex));
    AnimationFrameRect* bodyRect=new AnimationFrameRect();

    bodyRect->setWidth(20);
    bodyRect->setHeight(20);
    bodyRect->setX(0);
    bodyRect->setY(0);

    curFrame->addBodyRect(bodyRect);
    updateScene();

}

void MainWindow::addPhyRect()
{
    if(!model  )
    {
        return;
    }

    AnimationFrame* curFrame=static_cast<AnimationFrame*>(model->itemFromIndex(curFrameIndex));
    AnimationFrameRect* phyRect=new AnimationFrameRect();

    phyRect->setWidth(20);
    phyRect->setHeight(20);
    phyRect->setX(0);
    phyRect->setY(0);

    curFrame->addPhyRect(phyRect);
    updateScene();
}

void MainWindow::deleteAtkRect()
{
    if(!model  )
    {
        return;
    }

    QModelIndex curRectIndex=ui->atkRectView->currentIndex();

    QStandardItem* curRect=model->itemFromIndex(curRectIndex);
    QStandardItem* parent=curRect->parent();
    parent->removeRow(curRect->row());

    updateScene();
}

void MainWindow::deleteBodyRect()
{
    if(!model  )
    {
        return;
    }

    QModelIndex curRectIndex=ui->bodyRectView->currentIndex();

    QStandardItem* curRect=model->itemFromIndex(curRectIndex);
    QStandardItem* parent=curRect->parent();
    parent->removeRow(curRect->row());

    updateScene();
}

void MainWindow::deletePhyRect()
{
    if(!model  )
    {
        return;
    }

    QModelIndex curRectIndex=ui->phyRectView->currentIndex();

    QStandardItem* curRect=model->itemFromIndex(curRectIndex);
    QStandardItem* parent=curRect->parent();
    parent->removeRow(curRect->row());

    updateScene();
}

void MainWindow::addFrame()
{
    QString picFile=QFileDialog::getOpenFileName(this,
                                         tr("Open png file"),".",
                                         tr("png file(*.png)"));

    if(picFile.isEmpty())
    {
        return;
    }
    Animation* animation=static_cast<Animation*>(model->itemFromIndex(curAnimationIndex));
    animation->addFrame(picFile);

    updateFrameView();
}

void MainWindow::deleteFrame()
{
    scene->clear();
    QStandardItem* frame=model->itemFromIndex(curFrameIndex);
    frame->parent()->removeRow(frame->row());

    updateFrameView();
}

void MainWindow::addAnimation()
{
    bool ok=false;
    QString animationID=QInputDialog::getText(
                this,
                tr("animation ID"),
                tr("input animation ID"),
                 QLineEdit::Normal, QString::null, &ok);
    if(ok && !animationID.isEmpty())
    {
        Animation* newAnimation=new Animation();
        newAnimation->setID(animationID);
        animationBox->addAnimation(newAnimation);
        ui->animationView->setCurrentIndex(newAnimation->index());
        updateAnimationView();
    }
}

void MainWindow::deleteAnimation()
{
    QModelIndex curAnimationIndex=ui->animationView->currentIndex();

    //防止为当前animationBox为空
    if(curAnimationIndex.isValid())
    {
        QStandardItem* curAnimation=model->itemFromIndex(curAnimationIndex);
        curAnimation->parent()->removeRow(curAnimation->row());
    }
    updateAnimationView();
}

void MainWindow::selectRectObject(QModelIndex index)
{
    QList<QGraphicsItem*> allItem=scene->items();

    for(int i=0;i<allItem.size();i++)
    {
        allItem.at(i)->setSelected(false);
    }

    AnimationFrameRect* rect=static_cast<AnimationFrameRect*>(model->itemFromIndex(index));
    rect->selectObject();
}

void MainWindow::setViewToModel()
{
    ui->atkRectView->setModel(model);
    ui->bodyRectView->setModel(model);
    ui->phyRectView->setModel(model);
    ui->frameView->setModel(model);
    ui->animationView->setModel(model);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(closeFileSlot())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::printAnimationBox()
{
    for(int i=0;i<animationBox->rowCount();i++)
    {
        Animation* animation=static_cast<Animation*>(animationBox->child(i));

        std::cout<<animation->getID().toStdString()<<std::endl;

        for(int i=0;i<animation->rowCount();i++)
        {
            AnimationFrame* frame=static_cast<AnimationFrame*>(animation->child(i));

            std::cout<<frame->getSpriteName().toStdString()<<std::endl;
        }
    }
}

void MainWindow::connectActions()
{
    connect(ui->actionOpen,SIGNAL(triggered(bool)),this,SLOT(openFileSlot()));
    connect(ui->actionNew,SIGNAL(triggered(bool)),this,SLOT(newFileSlot()));
    connect(ui->actionSave,SIGNAL(triggered(bool)),this,SLOT(saveFileSlot()));
    connect(ui->actionClose,SIGNAL(triggered(bool)),this,SLOT(closeFileSlot()));

    connect(ui->animationView,SIGNAL(clicked(QModelIndex)),this,SLOT(updateAnimationView()));
    connect(ui->frameView,SIGNAL(clicked(QModelIndex)),this,SLOT(updateRectView()));

    connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(changeRectTab(int)));

    connect(ui->atkAddButton,SIGNAL(clicked(bool)),this,SLOT(addAtkRect()));
    connect(ui->bodyAddButton,SIGNAL(clicked(bool)),this,SLOT(addBodyRect()));
    connect(ui->phyAddButton,SIGNAL(clicked(bool)),this,SLOT(addPhyRect()));

    connect(ui->atkDeleteButton,SIGNAL(clicked(bool)),this,SLOT(deleteAtkRect()));
    connect(ui->bodyDeleteButton,SIGNAL(clicked(bool)),this,SLOT(deleteBodyRect()));
    connect(ui->phyDeleteButton,SIGNAL(clicked(bool)),this,SLOT(deletePhyRect()));

    connect(ui->atkRectView,SIGNAL(clicked(QModelIndex)),this,SLOT(selectRectObject(QModelIndex)));
    connect(ui->bodyRectView,SIGNAL(clicked(QModelIndex)),this,SLOT(selectRectObject(QModelIndex)));
    connect(ui->phyRectView,SIGNAL(clicked(QModelIndex)),this,SLOT(selectRectObject(QModelIndex)));

    connect(ui->frameAddButton,SIGNAL(clicked(bool)),this,SLOT(addFrame()));
    connect(ui->frameDeleteButton,SIGNAL(clicked(bool)),this,SLOT(deleteFrame()));

    connect(ui->animationAddButton,SIGNAL(clicked(bool)),this,SLOT(addAnimation()));
    connect(ui->animationDeleteButton,SIGNAL(clicked(bool)),this,SLOT(deleteAnimation()));
}

void MainWindow::open(const QString &filename)
{
    model=new QStandardItemModel();
    animationBox=new AnimationBox;
    model->appendRow(animationBox);


    setViewToModel();

    if(!filename.isEmpty()
                    && animationBox->init(filename))
    {
        curAnimationIndex=animationBox->child(0)->index();
        ui->animationView->setRootIndex(animationBox->index());
        ui->animationView->setCurrentIndex(curAnimationIndex);
        updateAnimationView();
    }
}

void MainWindow::closeFile()
{
    scene->clear();
    delete model;
    model=nullptr;
}

void MainWindow::showRect()
{
    int index=ui->tabWidget->currentIndex();
    switch(index)
    {
    case 0:
        showAtkRect();
        break;
    case 1:
        showBodyRect();
        break;
    case 2:
        showPhyRect();
        break;
    default:
        break;
    }
}

void MainWindow::showAtkRect()
{
    if(!model  )
    {
        return;
    }
    QModelIndex atkRootIndex=curFrameIndex.child(0,0);
    QStandardItem* root=model->itemFromIndex(atkRootIndex);

    for(int i=0;i<root->rowCount();i++)
    {
        AnimationFrameRect* rectItem=static_cast<AnimationFrameRect*>(root->child(i));

        RectObject* rectobject=new RectObject(rectItem);
        rectobject->setRectColor(QColor(255,0,0));
        scene->addItem(rectobject);
    }
    if(root->rowCount()>0)
    {
        ui->atkRectView->setCurrentIndex(root->child(0)->index());
        selectRectObject(root->child(0)->index());
    }
}

void MainWindow::showBodyRect()
{
    if(!model  )
    {
        return;
    }
    QModelIndex bodyRootIndex=curFrameIndex.child(1,0);
    QStandardItem* root=model->itemFromIndex(bodyRootIndex);

    for(int i=0;i<root->rowCount();i++)
    {
        AnimationFrameRect* rectItem=static_cast<AnimationFrameRect*>(root->child(i));


        RectObject* rectobject=new RectObject(rectItem);
        rectobject->setRectColor(QColor(0,0,255));
        //        scene->addItem(rectobject);
        //        rectobject->setParentItem(pixmapItem);
        scene->addItem(rectobject);
    }
    if(root->rowCount()>0)
    {
        ui->bodyRectView->setCurrentIndex(root->child(0)->index());
        selectRectObject(root->child(0)->index());
    }

}

void MainWindow::showPhyRect()
{
    if(!model  )
    {
        return;
    }
    QModelIndex phyRootIndex=curFrameIndex.child(2,0);
    QStandardItem* root=model->itemFromIndex(phyRootIndex);

    for(int i=0;i<root->rowCount();i++)
    {
        AnimationFrameRect* rectItem=static_cast<AnimationFrameRect*>(root->child(i));

        RectObject* rectobject=new RectObject(rectItem);
        rectobject->setRectColor(QColor(0,255,0));
        scene->addItem(rectobject);

    }
    if(root->rowCount()>0)
    {
        ui->phyRectView->setCurrentIndex(root->child(0)->index());
        selectRectObject(root->child(0)->index());
    }
}

void MainWindow::showSprite()
{
    if(!model  )
    {
        return;
    }
    QString spriteName=static_cast<AnimationFrame*>(model->itemFromIndex(curFrameIndex))->getSpriteName();
    pixmapItem=new QGraphicsPixmapItem(QPixmap(spriteName));
    pixmapItem->setPos(pixmapItem->pos().x(),-pixmapItem->boundingRect().height());
    scene->addItem(pixmapItem);
}

bool MainWindow::isModified()
{
    return modified;
}
