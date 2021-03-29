#include <QPoint>
#include "ParachuteWidget.h"

ParachuteWidget::ParachuteWidget(QWidget * parent, MessageModel * model) : QWidget(parent), _model(model)
{
    setFixedSize(200, 200);
}

void ParachuteWidget::setModel(MessageModel * model) {
    _model = model;
}

void ParachuteWidget::setNbSectors(int value) {
    _nbSectors = value;
}

void ParachuteWidget::setNbTracks(int value) {
    _nbTracks = value;
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
    QPoint points[_nbTracks][_nbSectors][4];

    float widget_width = width();
    float widget_heigth = height();

    float cx = widget_width / 2;
    float cy = widget_heigth / 2;

    float radius_max = cy - 20;

    float angle_step = static_cast<float>(2 * M_PI) / _nbSectors;
    float radius_step = radius_max / _nbTracks;

    float angle1 = 0;
    float radius1 = 0;
    float angle2 = angle_step;
    float radius2 = radius_step;

    for (int i = 0; i < _nbTracks; i++) {
        for (int j = 0; j < _nbSectors; j++) {
            QPoint * figure = points[i][_nbSectors - j - 1];
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
    for (int ind = 0; ind < _model->getRows()*_model->getColumns(); ind++){
        j = ind % _nbSectors;
        i = ind / _nbSectors;
        if (_model->getBinaryElement(ind) == 1){
            if (i < _nbTracks && j < _nbSectors){
                painter->setBrush(Qt::red);
                painter->drawPolygon(points[i][j], 4);
            }
        }
    }
}
