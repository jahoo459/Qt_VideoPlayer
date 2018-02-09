#include "videoplayerframe.h"
#include "ui_videoplayerframe.h"
#include <QMessageBox>
#include <QPixmap>

using namespace cv;

VideoPlayerFrame::VideoPlayerFrame(VideoExplorerFrame* fileExplorer, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::VideoPlayerFrame)
{
    this->m_fileExplorer = fileExplorer;
    player = new VideoPlayer(this);

    printLabel = true;

    QObject::connect(player, &VideoPlayer::newFrameRead, this, &VideoPlayerFrame::updateFrame);
    QObject::connect(this, &VideoPlayerFrame::sliderMoved, player, &VideoPlayer::onSliderMoved);
    ui->setupUi(this);
}

VideoPlayerFrame::~VideoPlayerFrame()
{
    player->terminate();
    delete player;
    delete ui;
}

void VideoPlayerFrame::saveFilePath(QString path)
{
    filePath = path.toStdString();
    fileLoaded = false;

    emit fileLoadedSig(tr("File loaded: ") + path);
}

bool VideoPlayerFrame::getPrintLabel() const
{
    return printLabel;
}

VideoPlayer *VideoPlayerFrame::getPlayer() const
{
    return player;
}


void VideoPlayerFrame::updateFrame(QImage img, int frameNo)
{

    if(!img.isNull())
    {
        QPixmap frame2Show = QPixmap::fromImage(img).scaled(ui->label_video->size(),
                                                                   Qt::KeepAspectRatio, Qt::FastTransformation);


        ui->label_frameCount->setText("Frame: " + QString::number(frameNo));
        ui->horizontalSlider->setValue(frameNo);
        ui->label_video->setAlignment(Qt::AlignCenter);

        try {
            ui->label_video->setPixmap(frame2Show);
        } catch (std::exception e) {
            qDebug() << "Exception catched: " << e.what();
        }

    }
}


void VideoPlayerFrame::on_pushButton_play_pause_clicked()
{

    if(!filePath.empty() && fileLoaded == false) //open file
    {
        if(player->getStopped() && player->getPaused()) //if is stopped and paused
        {
            player->openVideo(filePath);
            int totalFrameNumber = player->getTotalFrameCount();
            ui->horizontalSlider->setMaximum(totalFrameNumber);
            ui->horizontalSlider->setMinimum(0);

            fileLoaded = true;

            int arg1 = ui->horizontalSlider->value();
            if(arg1 > 0 && arg1 <6)
                player->updateInterval(arg1);

            player->setStopped(false);
            player->setPaused(false);

            player->start(QThread::NormalPriority); //start the player
        }
    }
    else if (fileLoaded == true && player->getPaused() == false)
    {
        player->setPaused(true);
    }
    else if (fileLoaded == true && player->getPaused() == true)
    {
        player->setPaused(false);
    }


}

void VideoPlayerFrame::on_speedSpinBox_valueChanged(double arg1)
{
    if(arg1 > 0 && arg1 <= 3)
        player->updateInterval(arg1);
}

void VideoPlayerFrame::on_pushButton_stop_clicked()
{
    player->setPaused(true);
    player->setStopped(true);
    fileLoaded = false;
    ui->horizontalSlider->setValue(0);
}

void VideoPlayerFrame::on_horizontalSlider_sliderMoved(int position)
{
    pickedValue = position;
}

void VideoPlayerFrame::on_horizontalSlider_sliderReleased()
{
    emit sliderMoved(pickedValue);
}

void VideoPlayerFrame::on_horizontalSlider_sliderPressed()
{
        player->setPaused(true);
}

void VideoPlayerFrame::on_pushButton_next_clicked()
{
    player->showSingleFrame(VideoPlayer::frameSingle::next);
}

void VideoPlayerFrame::on_pushButton_previous_clicked()
{
    player->showSingleFrame(VideoPlayer::frameSingle::previous);
}

void VideoPlayerFrame::on_checkBox_printLabel_clicked()
{
    printLabel = ui->checkBox_printLabel->isChecked();
}
