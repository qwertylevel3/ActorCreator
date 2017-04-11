#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"animationbox.h"
#include"rectobject.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionOpen,SIGNAL(triggered(bool)),this,SLOT(openFile()));
    connect(ui->actionNew,SIGNAL(triggered(bool)),this,SLOT(newFile()));
    connect(ui->actionSave,SIGNAL(triggered(bool)),this,SLOT(saveFile()));

    connect(ui->animationView,SIGNAL(clicked(QModelIndex)),this,SLOT(changeAnimation()));
    connect(ui->frameView,SIGNAL(clicked(QModelIndex)),this,SLOT(changeFrame()));

    connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(changeRectTab(int)));
    animationBox=new AnimationBox;
    model=new QStandardItemModel();
    model->appendRow(animationBox);

    ui->atkRectView->setModel(model);
    ui->bodyRectView->setModel(model);
    ui->phyRectView->setModel(model);
    ui->frameView->setModel(model);
    ui->animationView->setModel(model);

    view=new QGraphicsView(this);
    scene=new QGraphicsScene(this);

//    ui->scrollArea->setWidget(view);
    ui->dockWidget_3->setWidget(view);
    view->setScene(scene);
    view->setAcceptDrops(true);

    open("resource/animation.xml");

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1/60);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
}

void MainWindow::openFile()
{
    QString filename=QFileDialog::getOpenFileName(this,
                                                  tr("Open animation file"),".",
                                                  tr("animation file(*.xml)"));
    open(filename);

}

void MainWindow::newFile()
{
    std::cout<<"new"<<std::endl;
}

void MainWindow::saveFile()
{
    std::cout<<"save"<<std::endl;
}

void MainWindow::changeFrame()
{
    curFrameIndex=ui->frameView->currentIndex();

    QModelIndex atkRootIndex=curFrameIndex.child(0,0);
    QModelIndex bodyRootIndex=curFrameIndex.child(1,0);
    QModelIndex phyRootIndex=curFrameIndex.child(2,0);

    ui->atkRectView->setRootIndex(atkRootIndex);
    ui->bodyRectView->setRootIndex(bodyRootIndex);
    ui->phyRectView->setRootIndex(phyRootIndex);

    scene->clear();
    QString spriteName=static_cast<AnimationFrame*>(model->itemFromIndex(curFrameIndex))->getSpriteName();
    QGraphicsPixmapItem* pixmapItem=new QGraphicsPixmapItem(QPixmap(spriteName));
    scene->addItem(pixmapItem);

   // QRect rect=static_cast<AnimationFrameRect*>(model->itemFromIndex(atkRootIndex.child(0,0)))->getRect();

//    scene->addItem(new RectObject());
    showAtkRect();
}

void MainWindow::changeAnimation()
{
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

void MainWindow::open(const QString &filename)
{
    if(!filename.isEmpty()
                    && animationBox->init(filename))
    {
//        printAnimationBox();

        curAnimationIndex=animationBox->child(0)->index();
        ui->animationView->setRootIndex(animationBox->index());
        ui->animationView->setCurrentIndex(curAnimationIndex);
        changeAnimation();
    }
}

void MainWindow::showAtkRect()
{
    QModelIndex atkRootIndex=curFrameIndex.child(0,0);
    QStandardItem* root=model->itemFromIndex(atkRootIndex);

    for(int i=0;i<root->rowCount();i++)
    {
        AnimationFrameRect* rectItem=static_cast<AnimationFrameRect*>(root->child(i));

        QRect rect=rectItem->getRect();

        RectObject* rectobject=new RectObject();
        rectobject->setRect(rect);
        rectobject->setRectColor(QColor(255,0,0));
        scene->addItem(rectobject);
    }
}

void MainWindow::showBodyRect()
{
    QModelIndex bodyRootIndex=curFrameIndex.child(1,0);
    QStandardItem* root=model->itemFromIndex(bodyRootIndex);

    for(int i=0;i<root->rowCount();i++)
    {
        AnimationFrameRect* rectItem=static_cast<AnimationFrameRect*>(root->child(i));

        QRect rect=rectItem->getRect();

        RectObject* rectobject=new RectObject();
        rectobject->setRect(rect);
        rectobject->setRectColor(QColor(0,0,255));
        scene->addItem(rectobject);
    }
}

void MainWindow::showPhyRect()
{
    QModelIndex phyRootIndex=curFrameIndex.child(2,0);
    QStandardItem* root=model->itemFromIndex(phyRootIndex);

    for(int i=0;i<root->rowCount();i++)
    {
        AnimationFrameRect* rectItem=static_cast<AnimationFrameRect*>(root->child(i));

        QRect rect=rectItem->getRect();

        RectObject* rectobject=new RectObject();
        rectobject->setRect(rect);
        rectobject->setRectColor(QColor(0,255,0));
        scene->addItem(rectobject);
    }
}

void MainWindow::showSprite()
{
    QString spriteName=static_cast<AnimationFrame*>(model->itemFromIndex(curFrameIndex))->getSpriteName();
    QGraphicsPixmapItem* pixmapItem=new QGraphicsPixmapItem(QPixmap(spriteName));
    scene->addItem(pixmapItem);
}
