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
private:
    //debug
    void printAnimationBox();

    Ui::MainWindow *ui;
    AnimationBox* animationBox;
};

#endif // MAINWINDOW_H
