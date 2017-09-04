#include "category.h"

using namespace models;

Category::Category(const int &id, const QString &name):
    id_(id), name_(name)
{

}

const int &Category::getId() const
{
    return id_;
}

const QString &Category::getName() const
{
    return name_;
}
