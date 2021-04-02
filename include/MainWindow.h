#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MessageModel.h"
#include "ParachuteModel.h"
#include "SaveManager.h"
#include "LoadManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow * ui;
    MessageModel * _messageModel;
    ParachuteModel * _parachuteModel;
    SaveManager * _saveManager;
    LoadManager * _loadManager;

    void connectMenu();
    void connectEdit();
    void setMessageValidator();
    void changeMinimumValueSectorsTracks(int minSectors, int minTracks);

private slots:
    void onMessageChanged(const QString & message);
    void onSliderSectorsChanged(int value);
    void onSpinBoxSectorsChanged(int value);
    void onSliderTracksChanged(int value);
    void onSpinBoxTracksChanged(int value);

    void onQuit();
    void onAbout();
    void onSave();
    void onLoad();
};
#endif // MAINWINDOW_H
