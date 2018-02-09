#include "mainwindow.h"
#include <QList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)

{    
    centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    explorerFrame = new VideoExplorerFrame(videoFrame, this);
    videoFrame = new VideoPlayerFrame(explorerFrame, this);
    labelsFrame = new LabelsFrame(this);
    configLabelsDialog = new ConfigureLabelsDialog(this);
    newProjectDialog = new NewProjectDialog(this);
    historyWindow = new HistoryWindow(this);

    //Signals and Slots
    connect(explorerFrame, SIGNAL(pathSelected(QString)), videoFrame, SLOT(saveFilePath(QString)));
    connect(videoFrame, &VideoPlayerFrame::fileLoadedSig, this, &MainWindow::printInStatusBar);
    connect(newProjectDialog, &NewProjectDialog::newProjectCreated, this, &MainWindow::onNewProjectCreated);

    for(int i = 0; i < labelsFrame->categories.length(); i++)
    {
        connect(labelsFrame->categories.at(i), SIGNAL(labelAssigned(QString)), this, SLOT(onLabelAssigned(QString)));
    }

    //Build GUI
    QSplitter *vert_Splitter = new QSplitter;
    vert_Splitter->setOrientation(Qt::Vertical);

    QSplitter *hor_splitter = new QSplitter;
    hor_splitter->setOrientation(Qt::Horizontal);

    QSplitter *horSplitter2 = new QSplitter;
    horSplitter2->setOrientation(Qt::Horizontal);
    horSplitter2->addWidget(explorerFrame);
    horSplitter2->addWidget(historyWindow);

    hor_splitter->addWidget(videoFrame);
    hor_splitter->addWidget(horSplitter2);

    explorerFrame->setMinimumWidth(200);
    QList<int> horSplitterSizes = {3, 1};
    hor_splitter->setSizes(horSplitterSizes);
    hor_splitter->setStretchFactor(1, 0);


    vert_Splitter->addWidget(hor_splitter);
    vert_Splitter->addWidget(labelsFrame);

    QList<int> verSplitterSizes = {4, 1};
    vert_Splitter->setSizes(verSplitterSizes);

    this->mainLayout = new QHBoxLayout(centralWidget);

    mainLayout->addWidget(vert_Splitter);
    setLayout(mainLayout);

    setWindowTitle(tr("Advanced Traffic Analyzer"));

    statusBar()->showMessage(tr("Create or open a project..."));

    centralWidget->setEnabled(false);

    createMenuActions();
    createMenu();

}

MainWindow::~MainWindow()
{
    delete explorerFrame;
    delete videoFrame;
    delete centralWidget;
}

void MainWindow::createMenuActions()
{
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcut(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new project"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newProject);

    configureLabelsAct = new QAction(tr("&Configure Labels"), this);
    configureLabelsAct->setStatusTip(tr("Menage label categories"));
    connect(configureLabelsAct, &QAction::triggered, this, &MainWindow::configureLabels);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcut(QKeySequence::Save);
    saveAct->setStatusTip("Save current project");

}

void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(configureLabelsAct);
    fileMenu->addAction(saveAct);
}

void MainWindow::newProject()
{
    newProjectDialog->show();
}

void MainWindow::configureLabels()
{
    configLabelsDialog->show();
}

void MainWindow::save()
{

}

void MainWindow::printInStatusBar(QString msg)
{
    statusBar()->showMessage(msg);
}

void MainWindow::onNewProjectCreated()
{
    QString projectName = newProjectDialog->getProjectName();
    printInStatusBar("Project " + projectName + " created succesfully");
    QString projectPath = newProjectDialog->getProjectPath();
    QString description = newProjectDialog->getDescription();
    QString localization = newProjectDialog->getLocalization();
    QDate startDate = newProjectDialog->getStartDate();
    QDate endDate = newProjectDialog->getEndDate();

    if(!projectName.isEmpty() && !projectPath.isEmpty())
    {
        //TODO
        //Add description
        dbManager  = new DBManager(projectPath + "/projectData.db");
        labelsFrame->setDb(dbManager);

        dbManager->updateProjectDataTable(projectName, localization, projectPath, startDate, endDate);


        centralWidget->setEnabled(true);
    }
}

void MainWindow::onLabelAssigned(QString catname)
{
    qDebug() << "label " + catname + " assigned";
    //TODO save current frame + label to the database,
    QImage currFrame = videoFrame->getPlayer()->getImg();
    int currFrameNo = (int)videoFrame->getPlayer()->getActualFrameNumber();
    if(!currFrame.isNull())
    {
        //Add label text to the frame
        if(videoFrame->getPrintLabel())
        {
            QPainter painter(&currFrame);
            painter.setPen(Qt::red);
            painter.setFont(QFont("Times", 45, QFont::Bold));

            QPoint position(50,50);
            painter.drawText(position, catname);
        }


        //Save image to the database
        QFuture<void> future = QtConcurrent::run(dbManager, &DBManager::addLabelledFrame, currFrameNo, currFrame, catname);
        //future.waitForFinished();
        //dbManager->addLabelledFrame(currFrameNo, currFrame, catname);

        //Add frame to history widget
        historyWindow->addImageToList(currFrame);
    }
    else
    {
        qDebug() << "empty QImage!";
    }
}
