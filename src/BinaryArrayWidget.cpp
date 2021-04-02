#include "BinaryArrayWidget.h"
#include <iostream>

BinaryArrayWidget::BinaryArrayWidget(QWidget * parent, MessageModel * model) : QWidget(parent), _model(model)
{
}

void BinaryArrayWidget::setModel(MessageModel * model) {
    _model = model;
}

void BinaryArrayWidget::paintEvent(QPaintEvent * event) {
    Q_UNUSED(event);
    QPainter painter(this);
    drawBinaryArray(&painter);
}

void BinaryArrayWidget::drawBinaryArray(QPainter * painter) {
    int radius = height() / 7;

    if (_model->getColumns() > 8) {
        radius = width() / _model->getColumns();
    }

    for (int i = 0; i < _model->getRows(); i++) {
        for (int j = 0; j < _model->getColumns(); j++) {
            if (_model->getBinaryElement(i, j) == 0) {
                painter->setBrush(Qt::gray);
                painter->drawEllipse(j * radius, i * radius, radius, radius);
            } else {
                painter->setBrush(Qt::red);
                painter->drawEllipse(j * radius, i * radius, radius, radius);
            }
        }
    }
}
