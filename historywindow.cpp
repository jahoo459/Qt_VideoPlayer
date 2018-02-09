#include "historywindow.h"
#include "ui_historywindow.h"

#include <QListWidget>
#include <QListWidgetItem>

HistoryWindow::HistoryWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryWindow)
{
    ui->setupUi(this);
}

HistoryWindow::~HistoryWindow()
{
    delete ui;
}

bool HistoryWindow::addImageToList(QImage image)
{
    QImage img = image.scaledToWidth(ui->listWidget->width());
    QListWidgetItem *imgItem = new QListWidgetItem();
    imgItem->setData(Qt::DecorationRole, QPixmap::fromImage(img));
    ui->listWidget->insertItem(0, imgItem);
}
