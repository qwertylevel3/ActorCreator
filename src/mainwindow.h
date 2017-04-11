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
    void update();
    void changeRectTab(int index);

private:
    //debug
    void printAnimationBox();
    void open(const QString& filename);

    void showAtkRect();
    void showBodyRect();
    void showPhyRect();
    void showSprite();

    Ui::MainWindow *ui;
    AnimationBox* animationBox;
    QModelIndex curAnimationIndex;
    QModelIndex curFrameIndex;
    QStandardItemModel* model{nullptr};
    QGraphicsScene* scene;
    QGraphicsView* view;
};

#endif // MAINWINDOW_H
