#include "videoexplorerframe.h"
#include "ui_videoexplorerframe.h"
#include <QString>
#include <QFileDialog>
#include <QAbstractItemView>
#include <QMessageBox>


VideoExplorerFrame::VideoExplorerFrame(VideoPlayerFrame *videoPlayer, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::VideoExplorerFrame)
{
    this->m_videoPlayer = videoPlayer;
    ui->setupUi(this);
}

VideoExplorerFrame::~VideoExplorerFrame()
{
    delete ui;
}

void VideoExplorerFrame::on_pushButton_addVideoFiles_clicked()
{
    addVideoFiles();
    updateFileExplorer();
}

void VideoExplorerFrame::addVideoFiles()
{
    QStringList newFilenames = QFileDialog::getOpenFileNames(this, tr("Open Videos"), "C:/", tr("Video Files (*.avi *.wmv *.mp4)"));
    this->filenames.append(newFilenames);
    this->filenames.removeDuplicates();
}

void VideoExplorerFrame::updateFileExplorer()
{
    stringListModel = new QStringListModel;

    if(!this->filenames.empty())
    {
        this->stringListModel->setStringList(this->filenames);
        ui->listView->setModel(stringListModel);
        ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}


void VideoExplorerFrame::on_listView_doubleClicked(const QModelIndex &index)
{
    QString path = this->filenames.at(index.row());
    emit pathSelected(path);

}

QStringList VideoExplorerFrame::getFilenames() const
{
    return filenames;
}


