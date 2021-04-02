#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include <QObject>


class MessageModel : public QObject {
    Q_OBJECT
public:
    explicit MessageModel(QObject * parent = nullptr);

    const QString & getMessage() const;
    int getBinaryElement(int index);
    int getBinaryElement(int row, int col);
    int getRows();
    int getColumns();

public slots:
    void setMessage(const QString & message);

signals:
    void notify();

private:
    QString _message;
    std::vector<int> _binaryArray;

    void sendNotification();
    void resize();
    int asciiWithOffset(int ascii, int offset = 64);
    int * decimalToBinary(int number);
    void messageToBinary();
};

#endif // MESSAGEMODEL_H
