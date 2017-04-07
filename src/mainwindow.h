#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include"stable.h"
#include"animationbox.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected slots:
    void openFile();
    void newFile();
    void saveFile();
    void changeFrame();
    void changeAnimation();
private:
    //debug
    void printAnimationBox();

    Ui::MainWindow *ui;
    AnimationBox* animationBox;
    QModelIndex curAnimationIndex;
    QModelIndex curFrameIndex;
    QStandardItemModel* model{nullptr};
};

#endif // MAINWINDOW_H
