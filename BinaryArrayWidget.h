#ifndef BINARYARRAYWIDGET_H
#define BINARYARRAYWIDGET_H

#include <QWidget>
#include <QPainter>
#include "MessageModel.h"

class BinaryArrayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BinaryArrayWidget(QWidget * parent = nullptr, MessageModel * model = nullptr);

    void setModel(MessageModel * model);

private:
    MessageModel * _model;

    void paintEvent(QPaintEvent * event) override;
    void drawBinaryArray(QPainter * painter);
};

#endif // BINARYARRAYWIDGET_H
