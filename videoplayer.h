#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QWaitCondition>

#include "videoplayerframe.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc/imgproc.hpp>


class VideoPlayer : public QThread
{

    Q_OBJECT

public:
    VideoPlayer(QObject *parent = 0);
    ~VideoPlayer();

    enum frameSingle{
        previous,
        next
    };

    bool openVideo(std::string filename);
    void showSingleFrame(frameSingle frame);

    void setInterval(int value);
    void updateInterval(double arg);

    double getTotalFrameCount() const;

    void play();
    bool getStopped() const;
    void setStopped(bool value);

    bool getPaused() const;
    void setPaused(bool value);


    double getActualFrameNumber() const;

    QImage getImg() const;

signals:
    void newFrameRead(QImage img, int frameNo);

public slots:
    void onSliderMoved(int value);

private:
    bool stopped;
    bool paused;
    cv::Mat currentFrame;
    int interval;
    int originalInterval;
    double originalFPS;
    double frameWidth;
    double frameHeight;
    double actualFrameNumber;
    double actualVideoTime;
    double totalFrameCount;
    cv::VideoCapture capture;
    cv::Mat RGBFrame;
    QImage img;
    QWaitCondition condition;
    QMutex mutex;

    // QThread interface
protected:
    void run();
};

#endif // VIDEOPLAYER_H
