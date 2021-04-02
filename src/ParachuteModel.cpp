#include "ParachuteModel.h"

ParachuteModel::ParachuteModel(QObject * parent) : QObject(parent)
{
    _nbSectors = 21;
    _nbTracks = 5;
}

int ParachuteModel::getNbSectors() {
    return _nbSectors;
}

int ParachuteModel::getNbTracks() {
    return _nbTracks;
}

void ParachuteModel::sendNotification() {
    emit notify();
}

void ParachuteModel::setNbSectors(int nbSectors) {
    _nbSectors = nbSectors;
    sendNotification();
}
void ParachuteModel::setNbTracks(int nbTracks) {
    _nbTracks = nbTracks;
    sendNotification();
}
