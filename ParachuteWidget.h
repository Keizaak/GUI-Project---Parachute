#ifndef PARACHUTEWIDGET_H
#define PARACHUTEWIDGET_H

#include <QWidget>
#include <QPainter>
#include <math.h>
#include <iostream>
#include "MessageModel.h"

class ParachuteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ParachuteWidget(QWidget * parent = nullptr, MessageModel * _model = nullptr);

    void setModel(MessageModel * model);
    void setNbSectors(int value);
    void setNbTracks(int value);

private:
    MessageModel * _model;
    int _nbSectors = 21; // rows
    int _nbTracks = 5; // columns

    void paintEvent(QPaintEvent * event) override;
    void drawParachute(QPainter * painter);
    float createCoordinatesX(float radius, float angle, float cx);
    float createCoordinatesY(float radius, float angle, float cy);
};

#endif // PARACHUTEWIDGET_H
