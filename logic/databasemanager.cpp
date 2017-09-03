#include "databasemanager.h"
#include <QErrorMessage>
#include "exception/exception.h"
#include <QFile>
#include <QDebug>

DatabaseManager::DatabaseManager()
{   
    db_ = QSqlDatabase::addDatabase("QSQLITE");

    if ( !QFile::exists(dbName_) )
    {
        createDatabase_();
    }
    else
    {
        openDatabase_();
    }
}

const QVector<QString> DatabaseManager::getCategories()
{
    QVector<QString> result;
    QSqlQuery query(db_);
    if ( !query.exec("SELECT name FROM category") )
    {
        result.append(query.lastError().text());
        return result;
    }

    for (; query.next() ;)
    {
        result.append(query.value(0).toString());
    }

    return result;
}

void DatabaseManager::openDatabase_()
{
    db_.setDatabaseName(dbName_);
    if (!db_.open())
    {
        throw Exception("Ошибка базы данных: " + db_.lastError().text());
    }
}

void DatabaseManager::createDatabase_()
{
    openDatabase_();

    QFile sqlDumpFile(sqlDumpName_);
    if ( !sqlDumpFile.open(QIODevice::ReadOnly) )
    {
        throw Exception("Файл ресурса не может быть открыт");
    }
    QList<QByteArray> ddl = sqlDumpFile.readAll().split(';');
    sqlDumpFile.close();

    QSqlQuery query(db_);

    for ( QList<QByteArray>::iterator iterator = ddl.begin()++;
          iterator != ddl.end()--;
          iterator++ )
    {
        query.exec(iterator->data());
    }
}

DatabaseManager::~DatabaseManager()
{
    db_.close();
}
