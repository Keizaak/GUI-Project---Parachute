#include <QTranslator>
#include <QMessageBox>
#include <QFileDialog>
#include "MainWindow.h"
#include "ui_MainWindow.h"

// TODO: changer la trad à cause de l'ouverture de fichier
// TODO: minimum FACULTATIF
// TODO: barre icône OBLIGATOIRE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Crypted parachute"));

    setMessageValidator();

    _messageModel = new MessageModel(this);
    _parachuteModel = new ParachuteModel(this);

    ui->widgetBinaryArray->setModel(_messageModel);
    ui->widgetParachute->setMessageModel(_messageModel);
    ui->widgetParachute->setParachuteModel(_parachuteModel);

    connectEdit();
    connectMenu();

    _saveManager = new SaveManager();
    _loadManager = new LoadManager();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setMessageValidator() {
    QRegExp regExp("^[a-zA-Z@_]*$");
    QRegExpValidator * validator = new QRegExpValidator(regExp, this);
    ui->lineEditMessage->setValidator(validator);
}

void MainWindow::connectEdit() {
    connect(ui->lineEditMessage, SIGNAL(textChanged(const QString &)), this, SLOT(onMessageChanged(const QString &)));
    connect(ui->sliderSectors, SIGNAL(valueChanged(int)), this, SLOT(onSliderSectorsChanged(int)));
    connect(ui->spinBoxSectors, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxSectorsChanged(int)));
    connect(ui->sliderTracks, SIGNAL(valueChanged(int)), this, SLOT(onSliderTracksChanged(int)));
    connect(ui->spinBoxTracks, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxTracksChanged(int)));

    connect(_messageModel, SIGNAL(notify()), ui->widgetBinaryArray, SLOT(update()));
    connect(_messageModel, SIGNAL(notify()), ui->widgetParachute, SLOT(update()));
    connect(_parachuteModel, SIGNAL(notify()), ui->widgetParachute, SLOT(update()));
}

void MainWindow::changeMinimumValueSectorsTracks(int minSectors, int minTracks) {
    if (_parachuteModel->getNbTracks() * _parachuteModel->getNbSectors() < 7 * _messageModel->getMessage().length()) {
        ui->spinBoxSectors->setMinimum(minSectors);
        ui->sliderSectors->setMinimum(minSectors);
        ui->spinBoxTracks->setMinimum(minTracks);
        ui->sliderTracks->setMinimum(minTracks);
    }
}

void MainWindow::onMessageChanged(const QString & message) {
    _messageModel->setMessage(message);
    //changeMinimumValueSectorsTracks(7, 1);
}

void MainWindow::onSliderSectorsChanged(int value) {
    ui->spinBoxSectors->setValue(value);
    _parachuteModel->setNbSectors(value);
    //changeMinimumValueSectorsTracks(_parachuteModel->getNbSectors(), _parachuteModel->getNbTracks());
}

void MainWindow::onSpinBoxSectorsChanged(int value) {
    ui->sliderSectors->setValue(value);
    _parachuteModel->setNbSectors(value);
    //changeMinimumValueSectorsTracks(_parachuteModel->getNbSectors(), _parachuteModel->getNbTracks());
}

void MainWindow::onSliderTracksChanged(int value) {
    ui->spinBoxTracks->setValue(value);
    _parachuteModel->setNbTracks(value);
    //changeMinimumValueSectorsTracks(_parachuteModel->getNbSectors(), _parachuteModel->getNbTracks());
}

void MainWindow::onSpinBoxTracksChanged(int value) {
    ui->sliderTracks->setValue(value);
    _parachuteModel->setNbTracks(value);
    //changeMinimumValueSectorsTracks(_parachuteModel->getNbSectors(), _parachuteModel->getNbTracks());
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
        _parachuteModel->setNbSectors(nbSectors);
        ui->spinBoxTracks->setValue(nbTracks);
        _parachuteModel->setNbTracks(nbTracks);
        ui->lineEditMessage->setText(message);

        QMessageBox::information(this,
                                 tr("Load"),
                                 tr("Parachute settings have been loaded successfully"));
    } else {
        QMessageBox::critical(this,
                              tr("Load"),
                              tr("Parachute settings could not be loaded, your file is invalid"));
    }
}
