#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDate>
#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class NewProjectDialog;
}

class NewProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewProjectDialog(QWidget *parent = 0);
    ~NewProjectDialog();

    QDate getStartDate() const;
    QDate getEndDate() const;
    QString getProjectPath() const;
    QString getDescription() const;
    QString getProjectName() const;

    QString getLocalization() const;

signals:
    void newProjectCreated();

private slots:

    //void on_buttonBox_clicked(QAbstractButton *button);

    void on_pushButton_selectPath_clicked();

private:
    Ui::NewProjectDialog *ui;
    QString projectName;
    QString localization;
    QString description;
    QString projectPath;
    QDate startDate;
    QDate endDate;



    // QDialog interface
public slots:
    void done(int);
};

#endif // NEWPROJECTDIALOG_H
