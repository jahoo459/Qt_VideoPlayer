#include "categorycounterframe.h"
#include "ui_categorycounterframe.h"

CategoryCounterFrame::CategoryCounterFrame(QWidget *parent, QString name) :
    QFrame(parent),
    ui(new Ui::CategoryCounterFrame)
{
    this->m_name = name;
    this->value = 0;

    ui->setupUi(this);

    ui->pushButton->setText(m_name);
    ui->lcdNumber->setDecMode();
    ui->lcdNumber->display(QString::number(value));

}

CategoryCounterFrame::~CategoryCounterFrame()
{
    delete ui;
}

void CategoryCounterFrame::on_pushButton_clicked()
{
    value++;
    ui->lcdNumber->display(QString::number(value));

    emit labelAssigned(this->m_name);
}
