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
    void closeFile();
    void changeFrame();
    void changeAnimation();
    void update();
    void changeRectTab(int index);

private:
    //debug
    void printAnimationBox();

    void connectActions();

    void open(const QString& filename);
    void close();
//    void saveModel();

    void showAtkRect();
    void showBodyRect();
    void showPhyRect();
    void showSprite();

    bool isModified();

    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QGraphicsView* view;

    QStandardItemModel* model{nullptr};
    AnimationBox* animationBox;
    QModelIndex curAnimationIndex;
    QModelIndex curFrameIndex;

    QGraphicsPixmapItem* pixmapItem;

    QString curFile;
    bool modified;
};

#endif // MAINWINDOW_H
