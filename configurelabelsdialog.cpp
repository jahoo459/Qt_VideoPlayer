#include "configurelabelsdialog.h"
#include "ui_configurelabelsdialog.h"

ConfigureLabelsDialog::ConfigureLabelsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigureLabelsDialog)
{
    ui->setupUi(this);

    labelTableView = ui->tableView;
    model = new QStandardItemModel();

    labelTableView->setModel(model);

}

ConfigureLabelsDialog::~ConfigureLabelsDialog()
{
    delete ui;
}

void ConfigureLabelsDialog::on_pushButton_clicked()
{

}
