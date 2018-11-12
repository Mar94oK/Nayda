#-------------------------------------------------
#
# Project created by QtCreator 2017-04-09T00:43:10
#
#-------------------------------------------------

QT       += core gui
QT       += network widgets

#RESOURCES += tables.qrc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Nayda
TEMPLATE = app
CONFIG += c++14
CONFIG += resources_big

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
    Application/card.cpp \
    Application/player.cpp \
    battlefield.cpp \
    hand.cpp \
    popupcard.cpp \
    trianglecardpointer.cpp \
    cardstacks.cpp \
    handsecondaryplayer.cpp \
    rejectedcardmessage.cpp \
    handcardpointer.cpp \
    serversettings.cpp \
    helpserversettings.cpp \
    playMenu.cpp \
    gamesettings.cpp \
    serverMessageSystem.pb.cc \
    gamesettingswindow.cpp \
    roomcreationwaitinglobby.cpp \
    gamesettingswidget.cpp \
    serverhadclosedconnectionwindow.cpp

HEADERS  += main_application.h \
    Application/Before_The_Game/Before_The_Game.h \
    Application/The_Game/The_Game.h \
    System_Manager/system_manager.h \
    Server/server.h \
    gamerwidget.h \
    gametimers.h \
    gameinfowidget.h \
    Application/card.h \
    Application/player.h \
    battlefield.h \
    cardsborderdefines.h \
    hand.h \
    popupcard.h \
    trianglecardpointer.h \
    cardstacks.h \
    handsecondaryplayer.h \
    rejectedcardmessage.h \
    handcardpointer.h \
    munchkinglobaldefines.h \
    serversettings.h \
    helpserversettings.h \
    playMenu.h \
    gamesettings.h \
    serverMessageSystem.pb.h \
    gamesettingswindow.h \
    MessagesDefinitions.h \
    roomcreationwaitinglobby.h \
    gamesettingswidget.h \
    serverhadclosedconnectionwindow.h

FORMS    += main_application.ui \
    Application/Before_The_Game/Before_The_Game.ui \
    Application/The_Game/the_game.ui \
    gamerwidget.ui \
    gametimers.ui \
    gameinfowidget.ui \
    battlefield.ui \
    hand.ui \
    popupcard.ui \
    trianglecardpointer.ui \
    cardstacks.ui \
    handsecondaryplayer.ui \
    rejectedcardmessage.ui \
    handcardpointer.ui \
    serversettings.ui \
    helpserversettings.ui \
    playMenu.ui \
    gamesettingswindow.ui \
    roomcreationwaitinglobby.ui \
    gamesettingswidget.ui \
    serverhadclosedconnectionwindow.ui

RESOURCES += \
    tables.qrc \
    pictures.qrc \
    helpdocuments.qrc
    #pictures.qrc

DISTFILES += \
    Pictures/doorsAreOpened.jpg \
    ToDoList \
    Pictures/treasures_Weapon/Vorpal Blade.jpg \
    serverMessageSystem.proto

unix: LIBS += /usr/local/lib/libprotobuf.a
win32: LIBS += $$PWD/Libs/libprotobuf.a

win32: INCLUDEPATH += $$PWD/Includes
win32: DEPENDPATH += $$PWD/Includes

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/Libs/protobuf.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/Libs/libprotobuf.a
