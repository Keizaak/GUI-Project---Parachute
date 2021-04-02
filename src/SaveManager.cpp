#include <QDataStream>
#include <QFile>
#include <QFileDialog>
#include <QTranslator>
#include "SaveManager.h"

SaveManager::SaveManager()
{

}

bool SaveManager::save(QString fileName, qint32 nbSectors, qint32 nbTracks, QString message) {

    if (fileName.isEmpty()) {
        return false;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    QDataStream out(&file);
    out << nbSectors;
    out << nbTracks;
    out << message;

    return true;
}
