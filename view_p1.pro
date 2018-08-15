#-------------------------------------------------
#
# Project created by QtCreator 2018-02-16T08:05:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = view_p1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    src/main.cpp \
    src/drawing/GameScene.cpp \
    src/fool/Table.cpp \
    src/fool/Player.cpp \
    src/abstract/MyItem.cpp \
    src/drawing/GameItems.cpp \
    src/fool/Fool.cpp \
    src/fool/rules.cpp

HEADERS += \
    src/abstract/CardDeck.h \
    src/drawing/GameScene.h \
    src/fool/Player.h \
    src/fool/Table.h \
    src/abstract/GameElement.h \
    src/abstract/MyItem.h \
    src/drawing/GameItems.h \
    src/fool/fool.h \
    src/fool/rules.h

FORMS +=

RESOURCES += \
    pics.qrc
