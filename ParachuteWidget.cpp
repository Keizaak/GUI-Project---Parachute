#include <QPoint>
#include "ParachuteWidget.h"

ParachuteWidget::ParachuteWidget(QWidget * parent, MessageModel * model) : QWidget(parent), _model(model)
{

}

void ParachuteWidget::setModel(MessageModel * model) {
    _model = model;
}

void ParachuteWidget::paintEvent(QPaintEvent * event) {
    Q_UNUSED(event);
    QPainter painter(this);
    drawParachute(&painter);
}

void ParachuteWidget::drawParachute(QPainter * painter) {
    QPoint points[_model->getNbTracks()][_model->getNbSectors()][4];
    float angle = 0;
    float radius = 0;

    for (int i = 0; i < _model->getNbTracks(); i++) {
        for (int j = 0; j < _model->getSectors(); j++) {

        }
    }
}
