#ifndef HISTORYWINDOW_H
#define HISTORYWINDOW_H

#include <QWidget>

namespace Ui {
class HistoryWindow;
}

class HistoryWindow : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryWindow(QWidget *parent = 0);
    ~HistoryWindow();

    bool addImageToList(QImage image);
    bool onImageClicked(int imgNo);

private:
    Ui::HistoryWindow *ui;
    QList<QImage> imageList;
};

#endif // HISTORYWINDOW_H
