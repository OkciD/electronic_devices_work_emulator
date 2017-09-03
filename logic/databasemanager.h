#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql>

class DatabaseManager
{
public:
    static DatabaseManager &instance();
    const QVector<QString> getCategories();
    ~DatabaseManager();

private:
    DatabaseManager();
    void openDatabase_();
    void createDatabase_();
    DatabaseManager(const DatabaseManager &databaseManager);
    DatabaseManager &operator=(const DatabaseManager &databaseManager);

    QSqlDatabase db_;
    const QString dbName_ = "devices.db";
    const QString sqlDumpName_ = ":/resources/database/devices.sql";
};


#endif // DATABASEMANAGER_H
