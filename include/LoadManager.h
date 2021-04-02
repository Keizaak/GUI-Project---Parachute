#ifndef LOADMANAGER_H
#define LOADMANAGER_H

#include <QString>

class LoadManager
{
public:
    LoadManager();

    bool load(QString fileName, qint32 * nbSectors, qint32 * nbTracks, QString * message);
};

#endif // LOADMANAGER_H
