#include "Menu.h"

Menu::Menu(QMainWindow * parent) : QMenuBar(parent)
{
}

void Menu::onQuit() {
    close();
}

