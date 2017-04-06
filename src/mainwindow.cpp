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

    animationBox=new AnimationBox;
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

        if(model)
        {
            model->clear();
        }
        model=new QStandardItemModel(this);
        model->appendRow(animationBox);

        ui->atkRectView->setModel(model);
        ui->bodyRectView->setModel(model);
        ui->phyRectView->setModel(model);
        ui->frameView->setModel(model);
        ui->animationView->setModel(model);

        curAnimationIndex=animationBox->child(0)->index();
        curFrameIndex=animationBox->child(0)->child(0)->index();

        QModelIndex atkRootIndex=curFrameIndex.child(0,0);
        QModelIndex bodyRootIndex=curFrameIndex.child(1,0);
        QModelIndex phyRootIndex=curFrameIndex.child(2,0);


        ui->atkRectView->setRootIndex(atkRootIndex);
        ui->bodyRectView->setRootIndex(bodyRootIndex);
        ui->phyRectView->setRootIndex(phyRootIndex);

        ui->animationView->setRootIndex(animationBox->index());
        ui->frameView->setRootIndex(curAnimationIndex);
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

void MainWindow::printAnimationBox()
{
    for(int i=0;i<animationBox->rowCount();i++)
    {
        Animation* animation=static_cast<Animation*>(animationBox->child(i));

        std::cout<<animation->getID().toStdString()<<std::endl;

        for(int i=0;i<animation->rowCount();i++)
        {
            AnimationFrame* frame=static_cast<AnimationFrame*>(animation->child(i));

            std::cout<<frame->getSprite().toStdString()<<std::endl;
        }
    }
}
