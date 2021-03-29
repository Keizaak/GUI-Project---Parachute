#include <QDataStream>
#include <QFile>
#include "MessageModel.h"
#include <iostream>

MessageModel::MessageModel(QObject * parent) : QObject(parent)
{
    resize();
    messageToBinary();
}

int MessageModel::getNbTracks() const {
    return _nbTracks;
}

int MessageModel::getNbSectors() const {
    return _nbSectors;
}

const QString & MessageModel::getMessage() const {
  return _message;
}

int MessageModel::getBinaryElement(int index) {
    return _binaryArray[index];
}

int MessageModel::getBinaryElement(int row, int col) {
    return _binaryArray[row * _message.length() + col];
}

int MessageModel::getRows() {
    return 7;
}

int MessageModel::getColumns() {
    return _message.length();
}

void MessageModel::setNbTracks(const int nbTracks) {
    _nbTracks = nbTracks;
    sendNotification();
}
void MessageModel::setNbSectors(const int nbSectors) {
    _nbSectors = nbSectors;
    sendNotification();
}

void MessageModel::setMessage(const QString & message) {
    _message = message;
    resize();
    messageToBinary();
    sendNotification();
}

void MessageModel::sendNotification() {
    emit notify();
}

void MessageModel::resize() {
    _binaryArray.clear();
    _binaryArray.resize(7 *_message.length());
}

int MessageModel::asciiWithOffset(int ascii, int offset) {
    return ascii - offset;
}

int * MessageModel::decimalToBinary(int number) {
    static int binary[7];
    for (int j = 6; j >= 0; j--) {
        binary[j] = number % 2;
        number /= 2;
    }
    return binary;
}

void MessageModel::messageToBinary() {
    for (int i = 0; i < _message.length(); i++) {
        int number = asciiWithOffset(_message[i].toLatin1());
        int * binary = decimalToBinary(number);
        for (int j = 0; j < 7; j++) {
            _binaryArray[j * _message.length() + i] = binary[j];
        }
    }
}

bool MessageModel::save() {
    QFile file("parameters.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    out << (qint32)_nbSectors;
    out << (qint32)_nbTracks;
    out << _message;

    return true;
}

bool MessageModel::load() {
    QFile file("parameters.dat");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);

    in >> _nbSectors >> _nbTracks >> _message;
    sendNotification();

    return true;
}
