#ifndef PARACHUTEMODEL_H
#define PARACHUTEMODEL_H

#include <QObject>

class ParachuteModel : public QObject
{
    Q_OBJECT
public:
    explicit ParachuteModel(QObject * parent = nullptr);

    int getNbSectors();
    int getNbTracks();

public slots:
    void setNbSectors(int nbSectors);
    void setNbTracks(int nbTracks);

signals:
    void notify();

private:
    int _nbSectors; // columns
    int _nbTracks; // rows

    void sendNotification();
};

#endif // PARACHUTEMODEL_H
