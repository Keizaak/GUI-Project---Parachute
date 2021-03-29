#ifndef PARAMETERSSAVE_H
#define PARAMETERSSAVE_H

#include <QString>

class ParametersSave
{
public:
    ParametersSave();

    bool save(QString fileName, qint32 nbSectors, qint32 nbTracks, QString message);
};

#endif // PARAMETERSSAVE_H
