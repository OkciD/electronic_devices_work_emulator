#ifndef SOCKET_H
#define SOCKET_H

#include <QString>
#include <QStringList>

namespace models
{
class Socket
{
public:
    Socket(const int &id=0, const QString &name="", const QString &type="", const QString &conditionsString="");
    const int &getId() const;
    const QString &getName() const;
    const QString &getType() const;
    void setCurrentCondition(const QString &condition);
    const QString &getCurrentCondition() const;
    const QStringList &getConditions() const;

private:
    int id_;
    QString name_;
    QString type_;
    QString currentCondition_;
    QStringList conditions_;
};
}

#endif // SOCKET_H
