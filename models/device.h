#ifndef DEVICE_H
#define DEVICE_H

#include "category.h"
#include "socket.h"
#include <QVector>

namespace models
{
class Device
{
public:
    Device(const int &id=0, const int &categoryId=0, const QString &shortName="", const QString &fullName="");
    const int &getId() const;
    const Category &getCategory() const;
    const QString &getShortName() const;
    const QString &getFullName() const;
    QVector<Socket> &getInputSockets();
    QVector<Socket> &getOutputSockets();
    void calculateOutputSignal();

private:
    int id_;
    Category category_;
    QString shortName_;
    QString fullName_;
    QVector<Socket> inputSockets_;
    QVector<Socket> outputSockets_;
};
}


#endif // DEVICE_H
