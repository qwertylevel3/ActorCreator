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

    animationBox=new AnimationBox();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QString fileName=QFileDialog::getOpenFileName(this,
                                                  tr("Open animation file"),".",
                                                  tr("animation file(*.xml)"));

    if(!fileName.isEmpty()
                    && animationBox->init(fileName))
    {
        printAnimationBox();

        QStandardItemModel* model=new QStandardItemModel(this);
        model->appendRow(animationBox);

        ui->atkRectView->setModel(model);
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
