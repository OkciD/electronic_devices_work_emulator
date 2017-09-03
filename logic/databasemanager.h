#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql>

class DatabaseManager
{
public:
    DatabaseManager();
    const QVector<QString> getCategories();
    ~DatabaseManager();
private:
    QSqlDatabase db_;
    const QString dbName_ = "devices.db";
    const QString sqlDumpName_ = ":/database/devices.sql";
    void openDatabase_();
    void createDatabase_();
};


#endif // DATABASEMANAGER_H
