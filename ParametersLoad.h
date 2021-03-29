#ifndef PARAMETERSLOAD_H
#define PARAMETERSLOAD_H

#include <QString>

class ParametersLoad
{
public:
    ParametersLoad();

    bool load(QString fileName, qint32 * nbSectors, qint32 * nbTracks, QString * message);
};

#endif // PARAMETERSLOAD_H
