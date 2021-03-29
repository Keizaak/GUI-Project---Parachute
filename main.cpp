#include "MainWindow.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("Project_fr_FR");
    a.installTranslator(&translator);

    MainWindow w;
    w.show();
    return a.exec();
}
