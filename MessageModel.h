#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include <QObject>


class MessageModel : public QObject {
    Q_OBJECT
public:
    explicit MessageModel(QObject * parent = nullptr);

    int getNbTracks() const;
    int getNbSectors() const;
    const QString & getMessage() const;
    int getBinaryElement(int row, int col);
    int getRows();
    int getColumns();

public slots:
    void setNbTracks(const int nbTracks);
    void setNbSectors(const int nbSectors);
    void setMessage(const QString & message);

signals:
    void notify();

private:
    int _nbTracks = 5; // rows
    int _nbSectors = 21; // columns
    QString _message;
    std::vector<std::vector<int>> _binaryArray;

    void sendNotification();
    void resize();
    int asciiWithOffset(int ascii, int offset = 64);
    int * decimalToBinary(int number);
    void messageToBinary();
};

#endif // MESSAGEMODEL_H
