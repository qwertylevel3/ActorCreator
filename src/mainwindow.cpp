#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"animationbox.h"


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

    ui->scrollArea->setWidget(view);
    view->setScene(scene);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
}

void MainWindow::openFile()
{
    QString fileName=QFileDialog::getOpenFileName(this,
                                                  tr("Open animation file"),".",
                                                  tr("animation file(*.xml)"));

    if(!fileName.isEmpty()
                    && animationBox->init(fileName))
    {
//        printAnimationBox();

        curAnimationIndex=animationBox->child(0)->index();
        ui->animationView->setRootIndex(animationBox->index());
        ui->animationView->setCurrentIndex(curAnimationIndex);
        changeAnimation();
    }
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

}

void MainWindow::changeAnimation()
{
    curAnimationIndex=ui->animationView->currentIndex();
    curFrameIndex=curAnimationIndex.child(0,0);

    ui->frameView->setRootIndex(curAnimationIndex);
    ui->frameView->setCurrentIndex(curAnimationIndex.child(0,0));

    changeFrame();
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
