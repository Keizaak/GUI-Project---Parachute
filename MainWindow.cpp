#include <iostream>
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowTitle("Crypted parachute");
    ui->setupUi(this);

    QRegExp regExp("^[a-zA-Z@_]*$");
    QRegExpValidator * validator = new QRegExpValidator(regExp, this);
    ui->lineEditMessage->setValidator(validator);

    _model = new MessageModel(this);
    ui->widgetBinaryArray->setModel(_model);
    ui->widgetParachute->setModel(_model);

    connectEdit();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectEdit() {
    connect(ui->lineEditMessage, SIGNAL(textChanged(const QString &)), _model, SLOT(setMessage(const QString &)));
    connect(ui->sliderSectors, SIGNAL(valueChanged(int)), this, SLOT(onSliderSectorsChanged(int)));
    connect(ui->spinBoxSectors, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxSectorsChanged(int)));
    connect(ui->sliderTracks, SIGNAL(valueChanged(int)), this, SLOT(onSliderTracksChanged(int)));
    connect(ui->spinBoxTracks, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxTracksChanged(int)));

    connect(_model, SIGNAL(notify()), ui->widgetBinaryArray, SLOT(update()));
    connect(_model, SIGNAL(notify()), ui->widgetParachute, SLOT(update()));
}


void MainWindow::onSliderSectorsChanged(int value) {
    ui->spinBoxSectors->setValue(value);
    _model->setNbSectors(value);
}

void MainWindow::onSpinBoxSectorsChanged(int value) {
    ui->sliderSectors->setValue(value);
    _model->setNbSectors(value);
}

void MainWindow::onSliderTracksChanged(int value) {
    ui->spinBoxTracks->setValue(value);
    _model->setNbTracks(value);
}

void MainWindow::onSpinBoxTracksChanged(int value) {
    ui->sliderTracks->setValue(value);
    _model->setNbTracks(value);
}
