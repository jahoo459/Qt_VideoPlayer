#ifndef VIDEOEXPLORERFRAME_H
#define VIDEOEXPLORERFRAME_H


#include <QFrame>
#include <QList>
#include <QStringListModel>
#include "videoplayerframe.h"

class VideoPlayerFrame;

namespace Ui {
class VideoExplorerFrame;
}

class VideoExplorerFrame : public QFrame
{
    Q_OBJECT

public:
    explicit VideoExplorerFrame(VideoPlayerFrame *videoPlayer, QWidget *parent = 0);
    ~VideoExplorerFrame();

    QStringList getFilenames() const;

private slots:
    void on_pushButton_addVideoFiles_clicked();
    void on_listView_doubleClicked(const QModelIndex &index);

signals:
    void pathSelected(QString path);

private:
    Ui::VideoExplorerFrame *ui;

    VideoPlayerFrame *m_videoPlayer;

    QStringList filenames;
    QStringListModel *stringListModel;


    void addVideoFiles();
    void updateFileExplorer();

};

#endif // VIDEOEXPLORERFRAME_H
