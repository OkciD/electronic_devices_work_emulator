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
    const QVector<Category> getCategories();
    const Category getCategory(const int &categoryId);
    ~ModelsManager();

private:
    ModelsManager();
    void openDatabase_();
    void createDatabase_();
    const QSqlQuery executeQuery_(const QString &queryString);
    ModelsManager(const ModelsManager &databaseManager);
    ModelsManager &operator=(const ModelsManager &databaseManager);

    QSqlDatabase db_;
    const QString dbName_ = "devices.db";
    const QString sqlDumpName_ = ":/resources/database/devices.sql";
};
}

#endif // MODELSMANAGER_H
