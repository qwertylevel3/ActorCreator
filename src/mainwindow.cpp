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
                    && animationBox.init(fileName))
    {

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
    QList<Animation> allAnimation=animationBox.getAllAnimationRef();

    for(int i=0;i<allAnimation.size();i++)
    {
        Animation a=allAnimation.at(i);
        std::cout<<a.id.toStdString()<<std::endl;

        for(int j=0;j<a.frameList.size();j++)
        {
            std::cout<<a.frameList.at(j).sprite.toStdString()<<std::endl;
        }
    }
}
