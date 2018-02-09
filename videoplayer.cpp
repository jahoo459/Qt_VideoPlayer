#include "videoplayer.h"
#include "QDebug"

VideoPlayer::VideoPlayer(QObject *parent)
{
    qDebug() << "Player created!";
    interval = 100;
    stopped = true;
    paused = true;
}

VideoPlayer::~VideoPlayer()
{
    mutex.lock();
    stopped = true;
    capture.release();
    condition.wakeOne();
    mutex.unlock();
    wait();
}

bool VideoPlayer::openVideo(std::string filename)
{
    capture.open(filename);
    if(capture.isOpened())
    {
        //mutex.lock();
        originalFPS = capture.get(CV_CAP_PROP_FPS);
        frameWidth = capture.get(CV_CAP_PROP_FRAME_WIDTH);
        frameHeight = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
        actualFrameNumber = capture.get(CV_CAP_PROP_POS_FRAMES);
        actualVideoTime = capture.get(CV_CAP_PROP_POS_MSEC);
        totalFrameCount = capture.get(CV_CAP_PROP_FRAME_COUNT);

        originalInterval = 1 / originalFPS * 1000;
        interval = originalInterval;
        //mutex.unlock();
        return true;
    }

    return false;
}

void VideoPlayer::showSingleFrame(frameSingle frame)
{
    if(paused)
    {
        if(frame == previous)
        {
            int f = capture.get(CV_CAP_PROP_POS_FRAMES) - 2;
            capture.set(CV_CAP_PROP_POS_FRAMES, f);
        }

        if(capture.read(currentFrame))
        {
            if (currentFrame.channels()== 3){
                cv::cvtColor(currentFrame, RGBFrame, CV_BGR2RGB);
                img = QImage((const unsigned char*)(RGBFrame.data),
                             RGBFrame.cols,RGBFrame.rows,QImage::Format_RGB888);
            }
            else
            {
                img = QImage((const unsigned char*)(currentFrame.data),
                             currentFrame.cols,currentFrame.rows,QImage::Format_Indexed8);
            }

            emit newFrameRead(img, (int)actualFrameNumber);
        }
    }
}

void VideoPlayer::run()
{
    while(!stopped)
    {
        while(!paused)
        {
            if(!capture.read(currentFrame))
            {
                mutex.lock();
                stopped = true;
                mutex.unlock();
            }

            if (currentFrame.channels()== 3){
                cv::cvtColor(currentFrame, RGBFrame, CV_BGR2RGB);
                img = QImage((const unsigned char*)(RGBFrame.data),
                             RGBFrame.cols,RGBFrame.rows,QImage::Format_RGB888);
            }
            else
            {
                img = QImage((const unsigned char*)(currentFrame.data),
                             currentFrame.cols,currentFrame.rows,QImage::Format_Indexed8);
            }

            actualFrameNumber = capture.get(CV_CAP_PROP_POS_FRAMES);

            emit newFrameRead(img, (int)actualFrameNumber);

            msleep(interval);
        }

        //single frame forwards/backwards

        msleep(interval);

    }
}


void VideoPlayer::onSliderMoved(int value)
{
    //mutex.lock();
    if(!paused)
    {
        paused = true;

        actualFrameNumber = value;
        capture.set(CV_CAP_PROP_POS_FRAMES, value);

        paused = false;
    }
    else
    {
        actualFrameNumber = value;
        capture.set(CV_CAP_PROP_POS_FRAMES, value);
    }
    //mutex.unlock();
}

QImage VideoPlayer::getImg() const
{
    return img;
}

bool VideoPlayer::getPaused() const
{
    return paused;
}

void VideoPlayer::setPaused(bool value)
{
    //mutex.lock();
    paused = value;
    //mutex.unlock();
}

double VideoPlayer::getActualFrameNumber() const
{
    return actualFrameNumber;
}

void VideoPlayer::setStopped(bool value)
{
    //mutex.lock();
    stopped = value;
    //mutex.unlock();
}

bool VideoPlayer::getStopped() const
{
    return stopped;
}

double VideoPlayer::getTotalFrameCount() const
{
    return totalFrameCount;
}

void VideoPlayer::play()
{
    if(!isRunning())
    {
        if(getStopped())
        {
            stopped = false;
        }
        start();
    }
}

void VideoPlayer::updateInterval(double arg)
{
    //mutex.lock();
    interval = 1 / arg * originalInterval;
    //mutex.unlock();
}



