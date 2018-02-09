#ifndef LABELSFRAME_H
#define LABELSFRAME_H

#include <QFrame>
#include "categorycounterframe.h"
#include <QList>
#include <QBoxLayout>

class DBManager;

namespace Ui {
class LabelsFrame;
}

class LabelsFrame : public QFrame
{
    Q_OBJECT

public:
    explicit LabelsFrame(QWidget *parent = 0);
    ~LabelsFrame();

    void setDb(DBManager *db);

    QList<CategoryCounterFrame*> categories;

private:
    Ui::LabelsFrame *ui;

    DBManager* m_db;

};

#endif // LABELSFRAME_H
