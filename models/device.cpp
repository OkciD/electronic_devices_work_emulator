#include "device.h"
#include "modelsmanager.h"

using namespace models;

Device::Device(const int &id, const int &categoryId, const QString &shortName, const QString &fullName):
    id_(id), shortName_(shortName), fullName_(fullName)
{
    if ( categoryId != 0 )
    {
        category_ = ModelsManager::instance().getCategory(categoryId);
    }
    if ( id != 0 )
    {
        inputSockets_ = ModelsManager::instance().getDevicesSockets(id);
        for ( QVector<Socket>::iterator iterator = inputSockets_.begin();
              iterator != inputSockets_.end(); )
        {
            if ( iterator->getType() == "out" )
            {
                outputSockets_.append(inputSockets_.takeAt(iterator - inputSockets_.begin()));
            }
            else
            {
                iterator++;
            }
        }
    }
}

const int &Device::getId() const
{
    return id_;
}

const Category &Device::getCategory() const
{
    return category_;
}

const QString &Device::getShortName() const
{
    return shortName_;
}

const QString &Device::getFullName() const
{
    return fullName_;
}
