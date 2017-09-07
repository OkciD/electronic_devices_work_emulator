#include "socket.h"

using namespace models;

Socket::Socket(const int &id, const QString &name, const QString &type, const QString &conditionsString):
    id_(id), name_(name), type_(type), conditions_(conditionsString.split(" "))
{
    if ( !conditions_.empty() )
    {
        currentCondition_ = conditions_.first();
    }
    else
    {
        currentCondition_ = "";
    }
}

const int &Socket::getId() const
{
    return id_;
}

const QString &Socket::getName() const
{
    return name_;
}

const QString &Socket::getType() const
{
    return type_;
}

void Socket::setCurrentCondition(const QString &condition)
{
    currentCondition_ = condition;
}

const QString &Socket::getCurrentCondition() const
{
    return currentCondition_;
}

const QStringList &Socket::getConditions() const
{
    return conditions_;
}
