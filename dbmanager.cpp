#include "dbmanager.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QBuffer>


DBManager::DBManager(QString path, QObject *parent) : QObject(parent)
{
    if(!path.isEmpty())
    {
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName(path);

        if(!m_db.open())
        {
            qDebug() << "Connection error...";

            QMessageBox msg;
            msg.setText("Could not connect to the database!");
            msg.exec();
        }
        else
        {
            QString info = "Connected to the database";
            qDebug() << info;

            if(!createTables())
            {
                QMessageBox msg;
                msg.setText("Could not create basic database tables");
                msg.exec();
            }
            else
                qDebug() << "Tables created";
        }
    }
}

DBManager::~DBManager()
{

}

bool DBManager::createTables()
{
    QSqlQuery query(m_db);

    if(!query.exec("CREATE TABLE IF NOT EXISTS projectData("
                   "projectName TEXT,"
                   "location TEXT, "
                   "projectPath TEXT,"
                   "startDate DATE,"
                   "endDate DATE)"))
    {
        qDebug() << query.lastError();
        return false;
    }



    if(!query.exec("CREATE TABLE IF NOT EXISTS videoList("
                   "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "videoPath TEXT)"))
    {
        qDebug() << query.lastError();
        return false;
    }


    if(!query.exec("CREATE TABLE IF NOT EXISTS labelledFrameList("
                   "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "num INTEGER,"
                   "label TEXT,"
                   "frame BLOB)"))
    {
        qDebug() << query.lastError();
        return false;
    }


    return true;
}

bool DBManager::updateProjectDataTable(QString projName, QString loc, QString projPath, QDate sDate, QDate eDate)
{
    QSqlQuery query(m_db);

    query.prepare("INSERT INTO projectData (projectName, location, projectPath, startDate, endDate)"
                  "VALUES(:projName, :loc, :projPath, :sDate, :eDate)");

    query.bindValue(":projName", projName);
    query.bindValue(":loc", loc);
    query.bindValue(":projPath", projPath);
    query.bindValue(":sDate", sDate);
    query.bindValue(":eDate", eDate);

    if(query.exec())
        return true;
    else
    {
        qDebug() << "Could not fill projectData table";
        return false;
    }
}

//TODO Move saving Frame to DB to separate thread
bool DBManager::addLabelledFrame(int frameNo, QImage frame, QString label)
{
    QSqlQuery query(m_db);

    //write QImage into QByteArray
    QByteArray bArray;
    QBuffer buffer(&bArray);

    buffer.open(QIODevice::WriteOnly);
    frame.save(&buffer, "PNG");



    query.prepare("INSERT INTO labelledFrameList(num, label, frame)"
                  "VALUES(:num, :label, :frame)");


    query.bindValue(":num", frameNo);
    query.bindValue(":label", label);
    query.bindValue(":frame", bArray);


    if(!query.exec())
    {
        QMessageBox msg;
        msg.setText("Could not write labelled data");
        msg.exec();
        qDebug() << query.lastError();
        return false;
    }

    return true;
}


