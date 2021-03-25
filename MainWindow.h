#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MessageModel.h"

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

    void connectMenu();
    void connectEdit();

private slots:
    void onSliderSectorsChanged(int value);
    void onSpinBoxSectorsChanged(int value);
    void onSliderTracksChanged(int value);
    void onSpinBoxTracksChanged(int value);
};
#endif // MAINWINDOW_H
