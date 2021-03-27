#include <QPoint>
#include "ParachuteWidget.h"

ParachuteWidget::ParachuteWidget(QWidget * parent, MessageModel * model) : QWidget(parent), _model(model)
{
setFixedSize(300, 300);
}

void ParachuteWidget::setModel(MessageModel * model) {
    _model = model;
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
    QPoint points[_model->getNbTracks()][_model->getNbSectors()][4];

    float widget_width = width();
    float widget_heigth = height();
    std::cout << widget_width << widget_heigth << std::endl;
    float cx = widget_width / 2;
    float cy = widget_heigth / 2;

    float radius_max = cy - 20;

    float angle_step = static_cast<float>(2 * M_PI) / _model->getNbSectors();
    float radius_step = radius_max / _model->getNbTracks();

    float angle1 = 0;
    float radius1 = 0;
    float angle2 = angle_step;
    float radius2 = radius_step;

    for (int i = 0; i < _model->getNbTracks(); i++) {
        for (int j = 0; j < _model->getNbSectors(); j++) {
            QPoint * figure = points[i][j];
            figure[0].setX(static_cast<int>(createCoordinatesX(radius1,angle1,cx)));
            figure[0].setY(static_cast<int>(createCoordinatesY(radius1,angle1,cy)));

            figure[1].setX(static_cast<int>(createCoordinatesX(radius2,angle1,cx)));
            figure[1].setY(static_cast<int>(createCoordinatesY(radius2,angle1,cy)));

            figure[2].setX(static_cast<int>(createCoordinatesX(radius2,angle2,cx)));
            figure[2].setY(static_cast<int>(createCoordinatesY(radius2,angle2,cy)));

            figure[3].setX(static_cast<int>(createCoordinatesX(radius1,angle2,cx)));
            figure[3].setY(static_cast<int>(createCoordinatesY(radius1,angle2,cy)));

            if (i < _model->getRows() && j < _model->getColumns()){
                if(_model->getBinaryElement(i,j) == 1){

                    painter->setBrush(Qt::red);
                }else {

                    painter->setBrush(Qt::white);
                }
            }
            else {
                painter->setBrush(Qt::white);
            }
            painter->drawPolygon(figure, 4);
            angle1 += angle_step;
            angle2 += angle_step;
        }
        radius1 += radius_step;
        radius2 += radius_step;
    }
}
