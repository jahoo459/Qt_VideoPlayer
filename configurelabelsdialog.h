#ifndef CONFIGURELABELSDIALOG_H
#define CONFIGURELABELSDIALOG_H

#include <QDialog>
#include <QTableView>
#include <QKeySequence>
#include <QKeySequenceEdit>
#include <QStandardItem>
#include <QStandardItemModel>


namespace Ui {
class ConfigureLabelsDialog;
}

class ConfigureLabelsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigureLabelsDialog(QWidget *parent = 0);
    ~ConfigureLabelsDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ConfigureLabelsDialog *ui;

    QTableView *labelTableView;
    QKeySequenceEdit *sequenceEdit;
    QStandardItemModel *model;
};

#endif // CONFIGURELABELSDIALOG_H
