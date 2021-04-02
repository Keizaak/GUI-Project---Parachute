#include <QDataStream>
#include <QFile>
#include "LoadManager.h"

LoadManager::LoadManager()
{

}

bool LoadManager::load(QString fileName, qint32 * nbSectors, qint32 * nbTracks, QString * message) {

    if (fileName.isEmpty()) {
        return false;
    }

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QDataStream in(&file);
    message->clear();
    in >> *nbSectors >> *nbTracks >> *message;

    if (message->isEmpty()) {
        return false;
    }

    return true;
}
