#ifndef PARACHUTEWIDGET_H
#define PARACHUTEWIDGET_H

#include <QWidget>
#include <QPainter>
#include "MessageModel.h"

class ParachuteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ParachuteWidget(QWidget * parent = nullptr, MessageModel * _model = nullptr);

    void setModel(MessageModel * model);

private:
    MessageModel * _model;

    void paintEvent(QPaintEvent * event) override;
    void drawParachute(QPainter * painter);
};

#endif // PARACHUTEWIDGET_H
