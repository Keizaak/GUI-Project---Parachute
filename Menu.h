#ifndef MENU_H
#define MENU_H

#include "MainWindow.h"
#include <QMenuBar>

class Menu : public QMenuBar
{
    Q_OBJECT
public:
    Menu(QMainWindow * parent);

public slots:
    void onQuit();

private:

};

#endif // MENU_H
