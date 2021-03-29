#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MessageModel.h"
#include "ParametersSave.h"
#include "ParametersLoad.h"

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
    MessageModel * _model;
    ParametersSave * _saveManager;
    ParametersLoad * _loadManager;

    void connectMenu();
    void connectEdit();
    void setMessageValidator();
    void updateParachuteWidget();

private slots:
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
