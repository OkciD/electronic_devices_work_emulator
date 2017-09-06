#include "socket.h"

using namespace models;

Socket::Socket(const int &id, const QString &name, const QString &type):
    id_(id), name_(name), type_(type), condition_("")
{

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

void Socket::setCondition(const QString &condition)
{
    condition_ = condition;
}

const QString &Socket::getCondition() const
{
    return condition_;
}
