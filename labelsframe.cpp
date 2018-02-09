#include "labelsframe.h"
#include "ui_labelsframe.h"
#include <QDebug>

LabelsFrame::LabelsFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::LabelsFrame)
{
    categories.append(new CategoryCounterFrame(this, "car"));
    categories.append(new CategoryCounterFrame(this, "van"));
    categories.append(new CategoryCounterFrame(this, "lorry"));
    categories.append(new CategoryCounterFrame(this, "bicycle"));
    categories.append(new CategoryCounterFrame(this, "pedestrian"));

    //build GUI
    QHBoxLayout *layout = new QHBoxLayout;

    for(int i = 0; i < categories.size(); i++)
    {
        layout->addWidget(categories.at(i));
    }

    this->setLayout(layout);

    ui->setupUi(this);
}

LabelsFrame::~LabelsFrame()
{
    delete ui;
}

void LabelsFrame::setDb(DBManager *db)
{
    m_db = db;
}


