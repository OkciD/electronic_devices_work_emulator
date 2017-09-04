#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>

namespace models
{
class Category
{
public:
    Category(const int &id, const QString &name);
    const int &getId() const;
    const QString &getName() const;
private:
    int id_;
    QString name_;
};
}

#endif // CATEGORY_H
