#include <QMessageBox>
#include <iostream>
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Crypted parachute");

    QRegExp regExp("^[a-zA-Z@_]*$");
    QRegExpValidator * validator = new QRegExpValidator(regExp, this);
    ui->lineEditMessage->setValidator(validator);

    _model = new MessageModel(this);
    ui->widgetBinaryArray->setModel(_model);
    ui->widgetParachute->setModel(_model);

    connectEdit();
    connectMenu();
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

void MainWindow::connectMenu() {
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(onQuit()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(onAbout()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(onSave()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(onLoad()));
}

void MainWindow::onQuit() {
    close();
}

void MainWindow::onAbout() {
    QMessageBox::about(this,
                           "About",
                           "Crypted parachute - GUI Project\n(c) Raphaël ANCETTE & Camille GUIGNOL");
}

void MainWindow::onSave() {
    bool success = _model->save();

    if (success) {
        QMessageBox::information(this,
                                 "Save",
                                 "Parachute settings have been saved successfully");
    } else {
        QMessageBox::critical(this,
                              "Save",
                              "Parachute settings could not be saved, please try again");
    }
}

void MainWindow::onLoad() {

}
