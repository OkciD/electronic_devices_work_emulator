#include "modelsmanager.h"
#include <QErrorMessage>
#include "exception/exception.h"
#include <QFile>
#include <QDebug>

using namespace models;

ModelsManager &ModelsManager::instance()
{
    static ModelsManager instance;
    return instance;
}

ModelsManager::ModelsManager()
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

const QVector<Category> ModelsManager::getCategories()
{
    QVector<Category> result;
    QSqlQuery query = executeQuery_("SELECT id, name FROM category");

    for (; query.next() ;)
    {
        result.append(Category(query.value(0).toInt(), query.value(1).toString()));
    }

    return result;
}

const Category ModelsManager::getCategory(const int &categoryId)
{
    QSqlQuery query = executeQuery_("SELECT id, name FROM category WHERE id=" + QString::number(categoryId));

    query.next();
    return Category(query.value(0).toInt(), query.value(1).toString());
}

const QVector<Device> ModelsManager::getDevicesInCategory(const int &categoryId)
{
    QSqlQuery query = executeQuery_("SELECT id, short_name, full_name FROM device WHERE category_id=" + QString::number(categoryId));

    QVector<Device> result;
    for (; query.next() ;)
    {
        result.append(Device(query.value(0).toInt(), categoryId, query.value(1).toString(), query.value(2).toString()));
    }

    return result;
}

QVector<Socket> ModelsManager::getDevicesSockets(const int &deviceId)
{
    QSqlQuery query = executeQuery_("SELECT socket.id, socket.name, socket.type, truth_table.conditions "
                                    "FROM socket INNER JOIN truth_table ON truth_table.socket_id = socket.id "
                                    "WHERE truth_table.device_id = " + QString::number(deviceId));
    QVector<Socket> result;
    for (; query.next() ;)
    {
        result.append(Socket(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString()));
    }

    return result;
}

void ModelsManager::openDatabase_()
{
    db_.setDatabaseName(dbName_);
    if (!db_.open())
    {
        throw Exception("Ошибка базы данных: " + db_.lastError().text());
    }
}

void ModelsManager::createDatabase_()
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

const QSqlQuery ModelsManager::executeQuery_(const QString &queryString)
{
    QSqlQuery query(db_);

    if ( !query.exec(queryString) )
    {
        qDebug() << query.lastError();
        throw Exception("Невозможно выполнить запрос к базе данных");
    }

    return query;
}

ModelsManager::~ModelsManager()
{
    db_.close();
}
