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
public slots:
    void openFileSlot();
    void newFileSlot();
    void saveFileSlot();
    bool closeFileSlot();
protected slots:
    void updateRectView();
    void updateFrameView();
    void updateScene();
    void changeRectTab(int index);

    void addAtkRect();
    void addBodyRect();
    void addPhyRect();
    void deleteAtkRect();
    void deleteBodyRect();
    void deletePhyRect();

    //TODO
    void addFrame();
    void deleteFrame();

    void selectRectObject(QModelIndex index);
protected:
    void setViewToModel();
    void closeEvent(QCloseEvent *event);

    //debug
    void printAnimationBox();

    void connectActions();

    void open(const QString& filename);
    void closeFile();

    void showRect();
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
