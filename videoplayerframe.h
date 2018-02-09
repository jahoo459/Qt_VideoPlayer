#ifndef VIDEOPLAYERFRAME_H
#define VIDEOPLAYERFRAME_H

#include "videoexplorerframe.h"
#include "videoplayer.h"
#include <QFrame>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>

class VideoPlayer;
class VideoExplorerFrame;

namespace Ui {
class VideoPlayerFrame;
}

class VideoPlayerFrame : public QFrame
{
    Q_OBJECT

public:
    explicit VideoPlayerFrame(VideoExplorerFrame* fileExplorer, QWidget *parent = 0);
    ~VideoPlayerFrame();

    VideoPlayer *getPlayer() const;

    bool getPrintLabel() const;

public slots:
    void saveFilePath(QString path);

private:
    Ui::VideoPlayerFrame *ui;

    VideoExplorerFrame* m_fileExplorer;
    VideoPlayer *player;

    std::string filePath;
    bool fileLoaded;
    bool printLabel;

    int pickedValue;

signals:
    void sliderMoved(int value);
    void fileLoadedSig(QString filename);

private slots:
    void updateFrame(QImage img, int frameNo);
    void on_pushButton_play_pause_clicked();

    void on_speedSpinBox_valueChanged(double arg1);
//    void on_horizontalSlider_valueChanged(int value);
    void on_pushButton_stop_clicked();
    void on_horizontalSlider_sliderMoved(int position);
    void on_horizontalSlider_sliderReleased();
    void on_horizontalSlider_sliderPressed();
    void on_pushButton_next_clicked();
    void on_pushButton_previous_clicked();
    void on_checkBox_printLabel_clicked();
};

#endif // VIDEOPLAYERFRAME_H
