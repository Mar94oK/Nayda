/********************************************************************************
** Form generated from reading UI file 'Before_The_Game.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BEFORE_THE_GAME_H
#define UI_BEFORE_THE_GAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Before_The_Game
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QPushButton *Create_Lobby;
    QPushButton *Find_Lobby;
    QPushButton *Settings;
    QPushButton *About_Authors;
    QPushButton *pushButton;
    QPushButton *btnHide;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Before_The_Game)
    {
        if (Before_The_Game->objectName().isEmpty())
            Before_The_Game->setObjectName(QStringLiteral("Before_The_Game"));
        Before_The_Game->resize(1244, 797);
        centralWidget = new QWidget(Before_The_Game);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        Create_Lobby = new QPushButton(centralWidget);
        Create_Lobby->setObjectName(QStringLiteral("Create_Lobby"));

        verticalLayout->addWidget(Create_Lobby);

        Find_Lobby = new QPushButton(centralWidget);
        Find_Lobby->setObjectName(QStringLiteral("Find_Lobby"));

        verticalLayout->addWidget(Find_Lobby);

        Settings = new QPushButton(centralWidget);
        Settings->setObjectName(QStringLiteral("Settings"));

        verticalLayout->addWidget(Settings);

        About_Authors = new QPushButton(centralWidget);
        About_Authors->setObjectName(QStringLiteral("About_Authors"));

        verticalLayout->addWidget(About_Authors);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        btnHide = new QPushButton(centralWidget);
        btnHide->setObjectName(QStringLiteral("btnHide"));

        verticalLayout->addWidget(btnHide);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);

        Before_The_Game->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Before_The_Game);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1244, 22));
        Before_The_Game->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Before_The_Game);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Before_The_Game->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Before_The_Game);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Before_The_Game->setStatusBar(statusBar);

        retranslateUi(Before_The_Game);

        QMetaObject::connectSlotsByName(Before_The_Game);
    } // setupUi

    void retranslateUi(QMainWindow *Before_The_Game)
    {
        Before_The_Game->setWindowTitle(QApplication::translate("Before_The_Game", "\320\234\320\260\320\275\321\207\320\272\320\270\320\275 0.0.1", Q_NULLPTR));
        Create_Lobby->setText(QApplication::translate("Before_The_Game", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\267\320\260\320\273", Q_NULLPTR));
        Find_Lobby->setText(QApplication::translate("Before_The_Game", "\320\235\320\260\320\271\321\202\320\270 \320\267\320\260\320\273", Q_NULLPTR));
        Settings->setText(QApplication::translate("Before_The_Game", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", Q_NULLPTR));
        About_Authors->setText(QApplication::translate("Before_The_Game", "\320\236\320\261 \320\220\320\262\321\202\320\276\321\200\320\260\321\205", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Before_The_Game", "\320\222\321\213\321\205\320\276\320\264", Q_NULLPTR));
        btnHide->setText(QApplication::translate("Before_The_Game", "\320\235\320\260\321\207\320\260\320\273\320\276 (\320\236\321\202\320\273\320\260\320\264\320\272\320\260)", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Before_The_Game: public Ui_Before_The_Game {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BEFORE_THE_GAME_H
