#-------------------------------------------------
#
# Project created by QtCreator 2017-04-09T00:43:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Nayda
TEMPLATE = app
CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        main_application.cpp \
    Application/Before_The_Game/Before_The_Game.cpp \
    Application/The_Game/The_Game.cpp \
    Logs/errors.cpp \
    System_Manager/system_manager.cpp \
    Server/server.cpp \
    gamerwidget.cpp \
    gametimers.cpp \
    gameinfowidget.cpp \
    start_new_room.cpp \
    Application/card.cpp \
    Application/player.cpp \
    battlefield.cpp \
    hand.cpp \
    popupcard.cpp \
    trianglecardpointer.cpp

HEADERS  += main_application.h \
    Application/Before_The_Game/Before_The_Game.h \
    Application/The_Game/The_Game.h \
    System_Manager/system_manager.h \
    Server/server.h \
    gamerwidget.h \
    gametimers.h \
    gameinfowidget.h \
    start_new_room.h \
    Application/card.h \
    Application/player.h \
    battlefield.h \
    cardsborderdefines.h \
    hand.h \
    popupcard.h \
    trianglecardpointer.h

FORMS    += main_application.ui \
    Application/Before_The_Game/Before_The_Game.ui \
    Application/The_Game/the_game.ui \
    gamerwidget.ui \
    gametimers.ui \
    gameinfowidget.ui \
    start_new_room.ui \
    battlefield.ui \
    hand.ui \
    popupcard.ui \
    trianglecardpointer.ui
