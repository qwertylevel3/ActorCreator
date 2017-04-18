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

    //update
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1/60);
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
    std::cout<<"new"<<std::endl;
}

void MainWindow::saveFileSlot()
{
    animationBox->save(curFile);
}

void MainWindow::closeFileSlot()
{
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
        }
        else if(choose==QMessageBox::No)
        {
            closeFile();
        }
        else if(choose==QMessageBox::Cancel)
        {
            return;
        }
    }
    else
    {
        closeFile();
    }
}

void MainWindow::changeFrame()
{
    if(!model)
    {
        return;
    }
    curFrameIndex=ui->frameView->currentIndex();

    QModelIndex atkRootIndex=curFrameIndex.child(0,0);
    QModelIndex bodyRootIndex=curFrameIndex.child(1,0);
    QModelIndex phyRootIndex=curFrameIndex.child(2,0);

    ui->atkRectView->setRootIndex(atkRootIndex);
    ui->bodyRectView->setRootIndex(bodyRootIndex);
    ui->phyRectView->setRootIndex(phyRootIndex);

    scene->clear();

    showSprite();
    showAtkRect();
}

void MainWindow::changeAnimation()
{
    if(!model)
    {
        return;
    }
    curAnimationIndex=ui->animationView->currentIndex();
    curFrameIndex=curAnimationIndex.child(0,0);

    ui->frameView->setRootIndex(curAnimationIndex);
    ui->frameView->setCurrentIndex(curAnimationIndex.child(0,0));

    changeFrame();
}

void MainWindow::update()
{
    QMainWindow::update();
    view->update();
    scene->update();
}

void MainWindow::changeRectTab(int index)
{
    scene->clear();
    if(!model)
    {
        return;
    }
    showSprite();
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

void MainWindow::closeEvent(QCloseEvent *event)
{
    closeFileSlot();
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

    connect(ui->animationView,SIGNAL(clicked(QModelIndex)),this,SLOT(changeAnimation()));
    connect(ui->frameView,SIGNAL(clicked(QModelIndex)),this,SLOT(changeFrame()));

    connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(changeRectTab(int)));
}

void MainWindow::open(const QString &filename)
{
    model=new QStandardItemModel();
    animationBox=new AnimationBox;
    model->appendRow(animationBox);

    ui->atkRectView->setModel(model);
    ui->bodyRectView->setModel(model);
    ui->phyRectView->setModel(model);
    ui->frameView->setModel(model);
    ui->animationView->setModel(model);

    if(!filename.isEmpty()
                    && animationBox->init(filename))
    {
        curAnimationIndex=animationBox->child(0)->index();
        ui->animationView->setRootIndex(animationBox->index());
        ui->animationView->setCurrentIndex(curAnimationIndex);
        changeAnimation();
    }
}

void MainWindow::closeFile()
{
    scene->clear();
    delete model;
    model=nullptr;
}

void MainWindow::showAtkRect()
{
    if(!model)
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
}

void MainWindow::showBodyRect()
{
    if(!model)
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
}

void MainWindow::showPhyRect()
{
    if(!model)
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
}

void MainWindow::showSprite()
{
    if(!model)
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
