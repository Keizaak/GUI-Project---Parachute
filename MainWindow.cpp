#include <QTranslator>
#include <QMessageBox>
#include <QFileDialog>
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Crypted parachute"));

    _model = new MessageModel(this);
    ui->widgetBinaryArray->setModel(_model);
    ui->widgetParachute->setModel(_model);

    connectEdit();
    connectMenu();

    setMessageValidator();

    _saveManager = new ParametersSave();
    _loadManager = new ParametersLoad();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateParachuteWidget() {
    ui->widgetParachute->update();
}

void MainWindow::setMessageValidator() {
    QRegExp regExp("^[a-zA-Z@_]*$");
    QRegExpValidator * validator = new QRegExpValidator(regExp, this);
    ui->lineEditMessage->setValidator(validator);
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
    ui->widgetParachute->setNbSectors(value);
    updateParachuteWidget();
}

void MainWindow::onSpinBoxSectorsChanged(int value) {
    ui->sliderSectors->setValue(value);
    ui->widgetParachute->setNbSectors(value);
    updateParachuteWidget();
}

void MainWindow::onSliderTracksChanged(int value) {
    ui->spinBoxTracks->setValue(value);
    ui->widgetParachute->setNbTracks(value);
    updateParachuteWidget();
}

void MainWindow::onSpinBoxTracksChanged(int value) {
    ui->sliderTracks->setValue(value);
    ui->widgetParachute->setNbTracks(value);
    updateParachuteWidget();
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
                           tr("About"),
                           tr("Crypted parachute - GUI Project\n(c) Raphaël ANCETTE & Camille GUIGNOL"));
}

void MainWindow::onSave() {

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save parachute settings"),
                                                    "",
                                                    tr("Parachute settings (*.pst);;All Files (*)"));

    bool success = _saveManager->save(fileName,
                                      ui->spinBoxSectors->value(),
                                      ui->spinBoxTracks->value(),
                                      ui->lineEditMessage->text());

    if (success) {
        QMessageBox::information(this,
                                 tr("Save"),
                                 tr("Parachute settings have been saved successfully"));
    } else {
        QMessageBox::critical(this,
                              tr("Save"),
                              tr("Parachute settings could not be saved, please try again"));
    }
}

void MainWindow::onLoad() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open parachute settings"),
                                                    "",
                                                    tr("Parachute settings (*.pst);;All Files (*)"));

    qint32 nbSectors = ui->spinBoxSectors->value();
    qint32 nbTracks = ui->spinBoxTracks->value();
    QString message = ui->lineEditMessage->text();

    bool success = _loadManager->load(fileName,
                                      &nbSectors,
                                      &nbTracks,
                                      &message);

    if (success) {
        ui->spinBoxSectors->setValue(nbSectors);
        ui->widgetParachute->setNbSectors(nbSectors);
        ui->spinBoxTracks->setValue(nbTracks);
        ui->widgetParachute->setNbTracks(nbTracks);
        ui->lineEditMessage->setText(message);
        updateParachuteWidget();

        QMessageBox::information(this,
                                 tr("Load"),
                                 tr("Parachute settings have been loaded successfully"));
    } else {
        QMessageBox::critical(this,
                              tr("Load"),
                              tr("Parachute settings could not be loaded, your file is invalid"));
    }
}
