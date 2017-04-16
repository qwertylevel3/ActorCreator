#include "rectdialog.h"
#include "ui_rectdialog.h"

RectDialog::RectDialog(QWidget *parent,RectObject* rectObject) :
    QDialog(parent),
    ui(new Ui::RectDialog),
    rectObj(rectObject)
{
    ui->setupUi(this);

    QRectF rect=rectObj->rect();
    ui->wSpinBox->setValue(rect.width());
    ui->hSpinBox->setValue(rect.height());

    connect(ui->wSpinBox,SIGNAL(valueChanged(int)),this,SLOT(changeW(int)));
    connect(ui->hSpinBox,SIGNAL(valueChanged(int)),this,SLOT(changeH(int)));
}

RectDialog::~RectDialog()
{
    delete ui;
}

void RectDialog::changeW(int w)
{
    rectObj->setRectWidth(w);
}

void RectDialog::changeH(int h)
{
    rectObj->setRectHeight(h);
}
