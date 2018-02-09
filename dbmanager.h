#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>


class DBManager : public QObject
{
    Q_OBJECT
public:
    explicit DBManager(QString path, QObject *parent = 0);
    ~DBManager();

    bool updateProjectDataTable(QString projName, QString loc, QString projPath, QDate sDate, QDate eDate);
    bool addLabelledFrame(int frameNo, QImage frame, QString label);



private:
    QSqlDatabase m_db;

    bool createTables();

signals:
    void connectionSuccess(QString msg);

public slots:

};

#endif // DBMANAGER_H
