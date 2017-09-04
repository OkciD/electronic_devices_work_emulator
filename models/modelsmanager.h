#ifndef MODELSMANAGER_H
#define MODELSMANAGER_H

#include <QtSql>
#include "category.h"

namespace models
{
class ModelsManager
{
public:
    static ModelsManager &instance();
    const QVector<QString> getCategories();
    ~ModelsManager();

private:
    ModelsManager();
    void openDatabase_();
    void createDatabase_();
    ModelsManager(const ModelsManager &databaseManager);
    ModelsManager &operator=(const ModelsManager &databaseManager);

    QSqlDatabase db_;
    const QString dbName_ = "devices.db";
    const QString sqlDumpName_ = ":/resources/database/devices.sql";
};
}

#endif // MODELSMANAGER_H
