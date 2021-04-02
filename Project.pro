QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/BinaryArrayWidget.cpp \
    src/LoadManager.cpp \
    src/MainWindow.cpp \
    src/MessageModel.cpp \
    src/ParachuteModel.cpp \
    src/ParachuteWidget.cpp \
    src/SaveManager.cpp \
    src/main.cpp

HEADERS += \
    include/BinaryArrayWidget.h \
    include/LoadManager.h \
    include/MainWindow.h \
    include/MessageModel.h \
    include/ParachuteModel.h \
    include/ParachuteWidget.h \
    include/SaveManager.h


FORMS += \
    ressources/MainWindow.ui

TRANSLATIONS += \
    ressources/Project_fr_FR.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    OQilkK.json \
    README.md \
    etc/gui.jpg \
    ressources/Project_fr_FR.ts \
    xHpbFR.json
