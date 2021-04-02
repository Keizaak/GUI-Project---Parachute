#ifndef PARACHUTEWIDGET_H
#define PARACHUTEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <math.h>
#include <iostream>
#include "MessageModel.h"
#include "ParachuteModel.h"

class ParachuteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ParachuteWidget(QWidget * parent = nullptr);

    void setMessageModel(MessageModel * model);
    void setParachuteModel(ParachuteModel * model);

private:
    MessageModel * _messageModel;
    ParachuteModel * _parachuteModel;

    void paintEvent(QPaintEvent * event) override;
    void drawParachute(QPainter * painter);
    float createCoordinatesX(float radius, float angle, float cx);
    float createCoordinatesY(float radius, float angle, float cy);
};

#endif // PARACHUTEWIDGET_H
