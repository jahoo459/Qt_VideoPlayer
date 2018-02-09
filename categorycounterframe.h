#ifndef CATEGORYCOUNTERFRAME_H
#define CATEGORYCOUNTERFRAME_H

#include <QFrame>
#include <QString>

namespace Ui {
class CategoryCounterFrame;
}

class CategoryCounterFrame : public QFrame
{
    Q_OBJECT

public:
    explicit CategoryCounterFrame(QWidget *parent = 0, QString name = "");
    ~CategoryCounterFrame();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CategoryCounterFrame *ui;
    int value;
    QString m_name;

signals:
    void labelAssigned(QString catName);

};

#endif // CATEGORYCOUNTERFRAME_H
