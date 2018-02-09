#include "newprojectdialog.h"
#include "ui_newprojectdialog.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QTextEdit>

NewProjectDialog::NewProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectDialog)
{
    ui->setupUi(this);
}

NewProjectDialog::~NewProjectDialog()
{
    delete ui;
}

QDate NewProjectDialog::getStartDate() const
{
    return startDate;
}

QDate NewProjectDialog::getEndDate() const
{
    return endDate;
}

QString NewProjectDialog::getProjectPath() const
{
    return projectPath;
}

QString NewProjectDialog::getDescription() const
{
    return description;
}

QString NewProjectDialog::getProjectName() const
{
    return projectName;
}


void NewProjectDialog::done(int res)
{
    if(res == QDialog::Accepted)
    {
        QMessageBox msg;
        msg.setText("You have to provide all needed information!");

        //read all project data
        projectName = ui->lineEdit_projectName->text();
        startDate = ui->dateTimeEdit_startDate->date();
        endDate = ui->dateTimeEdit_endDate->date();
        description = ui->textEdit_description->toPlainText();
        localization = ui->lineEdit_Localization->text();


        if(projectName.isEmpty() || startDate.isNull() || endDate.isNull()
                || description.isEmpty())
        {
            msg.exec();
            return;
        }
    }

    emit newProjectCreated();
    QDialog::done(res);
}

//void NewProjectDialog::on_buttonBox_clicked(QAbstractButton *button)
//{
//    this->accept();
//}

void NewProjectDialog::on_pushButton_selectPath_clicked()
{
    QFileDialog dirDialog(this);

    dirDialog.setFileMode(QFileDialog::Directory);
    dirDialog.setDirectory("C:/");
    dirDialog.setOption(QFileDialog::ShowDirsOnly, true);
    dirDialog.setNameFilter("Any files (*)");

    if(dirDialog.exec())
    {
        QStringList selectedFiles;
        selectedFiles = dirDialog.selectedFiles();
        projectPath = selectedFiles.at(0);

        ui->lineEdit_projectPath->setText(projectPath);
    }

}

QString NewProjectDialog::getLocalization() const
{
    return localization;
}
