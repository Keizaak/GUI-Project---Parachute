#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <QString>

class SaveManager
{
public:
    SaveManager();

    bool save(QString fileName, qint32 nbSectors, qint32 nbTracks, QString message);
};

#endif // SAVEMANAGER_H
