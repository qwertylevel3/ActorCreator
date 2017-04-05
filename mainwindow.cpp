#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"animationbox.h"
#include<iostream>
using namespace std;




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    AnimationBox testBox;
    if(testBox.init("animation.xml"))
    {
        cout<<"success"<<endl;
        QList<Animation>& a=testBox.getAllAnimationRef();

        for(int i=0;i<a.size();i++)
        {
            cout<<a.at(i).id.toStdString()<<endl;

            QList<AnimationFrame> frameList=a.at(i).frameList;
            for(int j=0;j<frameList.size();j++)
            {
                cout<<frameList.at(j).sprite.toStdString()<<endl;
            }

        }
    }
    else
    {
        cout<<"faild"<<endl;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
