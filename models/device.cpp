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

QVector<Socket> &Device::getInputSockets()
{
    return inputSockets_;
}

QVector<Socket> &Device::getOutputSockets()
{
    return outputSockets_;
}


void Device::calculateOutputSignal()
{
    size_t i = 0;
    for ( ; i < inputSockets_[0].getConditions().length(); ++i )
    {
        size_t j = 0;
        for ( ; j < inputSockets_.length(); ++j )
        {
            if ( inputSockets_[j].getCurrentCondition() != inputSockets_[j].getConditions()[i] )
            {
                break;
            }
        }
        if ( j == inputSockets_.length() )
        {
            break;
        }
    }

    for ( QVector<Socket>::iterator iterator = outputSockets_.begin();
          iterator != outputSockets_.end();
          iterator++ )
    {
        iterator->setCurrentCondition(iterator->getConditions()[i]);
    }
}
