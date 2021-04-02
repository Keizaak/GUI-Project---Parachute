#include <QPoint>
#include "ParachuteWidget.h"

ParachuteWidget::ParachuteWidget(QWidget * parent) : QWidget(parent)
{
}

void ParachuteWidget::setMessageModel(MessageModel * model) {
    _messageModel = model;
}

void ParachuteWidget::setParachuteModel(ParachuteModel * model) {
    _parachuteModel = model;
}

void ParachuteWidget::paintEvent(QPaintEvent * event) {
    Q_UNUSED(event);
    QPainter painter(this);
    drawParachute(&painter);
}

float ParachuteWidget::createCoordinatesX(float radius, float angle, float cx){
    return radius*cos(angle) + cx;
}

float ParachuteWidget::createCoordinatesY(float radius, float angle,float cy){
    return -radius*sin(angle) + cy;
}


void ParachuteWidget::drawParachute(QPainter * painter) {
    QPoint points[_parachuteModel->getNbTracks()][_parachuteModel->getNbSectors()][4];

    float widget_width = width();
    float widget_heigth = height();

    float cx = widget_width / 2;
    float cy = widget_heigth / 2;

    float radius_max = cy - 20;

    float angle_step = static_cast<float>(2 * M_PI) / _parachuteModel->getNbSectors();
    float radius_step = radius_max / _parachuteModel->getNbTracks();

    float angle1 = 0;
    float radius1 = 0;
    float angle2 = angle_step;
    float radius2 = radius_step;

    for (int i = 0; i < _parachuteModel->getNbTracks(); i++) {
        for (int j = 0; j < _parachuteModel->getNbSectors(); j++) {
            QPoint * figure = points[i][_parachuteModel->getNbSectors() - j - 1];
            figure[0].setX(static_cast<int>(createCoordinatesX(radius1,angle1,cx)));
            figure[0].setY(static_cast<int>(createCoordinatesY(radius1,angle1,cy)));

            figure[1].setX(static_cast<int>(createCoordinatesX(radius2,angle1,cx)));
            figure[1].setY(static_cast<int>(createCoordinatesY(radius2,angle1,cy)));

            figure[2].setX(static_cast<int>(createCoordinatesX(radius2,angle2,cx)));
            figure[2].setY(static_cast<int>(createCoordinatesY(radius2,angle2,cy)));

            figure[3].setX(static_cast<int>(createCoordinatesX(radius1,angle2,cx)));
            figure[3].setY(static_cast<int>(createCoordinatesY(radius1,angle2,cy)));


            painter->setBrush(Qt::white);
            painter->drawPolygon(figure, 4);
            angle1 += angle_step;
            angle2 += angle_step;
        }
        radius1 += radius_step;
        radius2 += radius_step;
    }

    int i = 0;
    int j = 0;
    for (int ind = 0; ind < _messageModel->getRows()*_messageModel->getColumns(); ind++){
        j = ind % _parachuteModel->getNbSectors();
        i = ind / _parachuteModel->getNbSectors();
        if (_messageModel->getBinaryElement(ind) == 1){
            if (i < _parachuteModel->getNbTracks() && j < _parachuteModel->getNbSectors()){
                painter->setBrush(Qt::red);
                painter->drawPolygon(points[i][j], 4);
            }
        }
    }
}
