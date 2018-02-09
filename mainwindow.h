#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QFuture>
#include <QtConcurrent>

#include "videoexplorerframe.h"
#include "videoplayerframe.h"
#include "labelsframe.h"
#include "configurelabelsdialog.h"
#include "newprojectdialog.h"
#include "dbmanager.h"
#include "historywindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QWidget *centralWidget;
    QHBoxLayout *mainLayout;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    VideoExplorerFrame *explorerFrame;
    VideoPlayerFrame *videoFrame;
    LabelsFrame *labelsFrame;
    ConfigureLabelsDialog *configLabelsDialog;
    NewProjectDialog *newProjectDialog;
    DBManager *dbManager;
    HistoryWindow *historyWindow;

    QMenu *fileMenu;

    void createMenuActions();
    void createMenu();

    QAction *newAct;
    QAction *configureLabelsAct;
    QAction *saveAct;


private slots:
    void newProject();
    void configureLabels();
    void save();
    void printInStatusBar(QString msg);
    void onNewProjectCreated();

    void onLabelAssigned(QString catname);

};

#endif // MAINWINDOW_H
