#include <QDataStream>
#include <QFile>
#include "ParametersLoad.h"

ParametersLoad::ParametersLoad()
{

}

bool ParametersLoad::load(QString fileName, qint32 * nbSectors, qint32 * nbTracks, QString * message) {

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
