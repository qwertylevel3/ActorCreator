#ifndef RECTDIALOG_H
#define RECTDIALOG_H

#include <QDialog>
#include"rectobject.h"

namespace Ui {
class RectDialog;
}

class RectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RectDialog(QWidget *parent = 0,RectObject* rectObject=nullptr);
    ~RectDialog();

protected slots:
    void changeW(int w);
    void changeH(int h);
private:
    Ui::RectDialog *ui;
    RectObject* rectObj;
};

#endif // RECTDIALOG_H
