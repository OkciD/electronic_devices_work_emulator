#ifndef SOCKET_H
#define SOCKET_H

#include <QString>

namespace models
{
class Socket
{
public:
    Socket(const int &id=0, const QString &name="", const QString &type="");
    const int &getId() const;
    const QString &getName() const;
    const QString &getType() const;
    void setCondition(const QString &condition);
    const QString &getCondition() const;

private:
    int id_;
    QString name_;
    QString type_;
    QString condition_;
};
}

#endif // SOCKET_H
