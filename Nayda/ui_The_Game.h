/********************************************************************************
** Form generated from reading UI file 'the_game.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THE_GAME_H
#define UI_THE_GAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <battlefield.h>
#include <cardstacks.h>
#include <gameinfowidget.h>
#include <gamerwidget.h>
#include <gametimers.h>

QT_BEGIN_NAMESPACE

class Ui_The_Game
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *right_side_opponents_layout;
    QVBoxLayout *verticalLayout_5;
    CardStacks *CardStacksWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_7;
    QPushButton *btn_switch_back;
    QVBoxLayout *verticalLayout_6;
    GameInfoWidget *GameInfoBox;
    GameTimers *TimersWidget;
    QHBoxLayout *horizontalLayout_5;
    battleField *GameField;
    QHBoxLayout *horizontalLayout;
    GamerWidget *MainGamer;
    QHBoxLayout *top_opponents_layout;
    QMenuBar *menubar;
    QMenu *menuStart;
    QMenu *menuOptions;
    QMenu *menuAbout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *The_Game)
    {
        if (The_Game->objectName().isEmpty())
            The_Game->setObjectName(QStringLiteral("The_Game"));
        The_Game->resize(1141, 664);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(The_Game->sizePolicy().hasHeightForWidth());
        The_Game->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(The_Game);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        right_side_opponents_layout = new QVBoxLayout();
        right_side_opponents_layout->setObjectName(QStringLiteral("right_side_opponents_layout"));

        verticalLayout_3->addLayout(right_side_opponents_layout);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        CardStacksWidget = new CardStacks(centralwidget);
        CardStacksWidget->setObjectName(QStringLiteral("CardStacksWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(CardStacksWidget->sizePolicy().hasHeightForWidth());
        CardStacksWidget->setSizePolicy(sizePolicy1);

        verticalLayout_5->addWidget(CardStacksWidget);


        verticalLayout_3->addLayout(verticalLayout_5);


        gridLayout->addLayout(verticalLayout_3, 0, 2, 3, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        btn_switch_back = new QPushButton(centralwidget);
        btn_switch_back->setObjectName(QStringLiteral("btn_switch_back"));

        verticalLayout_7->addWidget(btn_switch_back);


        verticalLayout_2->addLayout(verticalLayout_7);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        GameInfoBox = new GameInfoWidget(centralwidget);
        GameInfoBox->setObjectName(QStringLiteral("GameInfoBox"));

        verticalLayout_6->addWidget(GameInfoBox);

        TimersWidget = new GameTimers(centralwidget);
        TimersWidget->setObjectName(QStringLiteral("TimersWidget"));
        sizePolicy1.setHeightForWidth(TimersWidget->sizePolicy().hasHeightForWidth());
        TimersWidget->setSizePolicy(sizePolicy1);

        verticalLayout_6->addWidget(TimersWidget);


        verticalLayout_2->addLayout(verticalLayout_6);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 3, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        GameField = new battleField(centralwidget);
        GameField->setObjectName(QStringLiteral("GameField"));

        horizontalLayout_5->addWidget(GameField);


        gridLayout->addLayout(horizontalLayout_5, 1, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        MainGamer = new GamerWidget(centralwidget);
        MainGamer->setObjectName(QStringLiteral("MainGamer"));

        horizontalLayout->addWidget(MainGamer);


        gridLayout->addLayout(horizontalLayout, 2, 1, 1, 1);

        top_opponents_layout = new QHBoxLayout();
        top_opponents_layout->setObjectName(QStringLiteral("top_opponents_layout"));

        gridLayout->addLayout(top_opponents_layout, 0, 1, 1, 1);

        The_Game->setCentralWidget(centralwidget);
        menubar = new QMenuBar(The_Game);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1141, 20));
        menuStart = new QMenu(menubar);
        menuStart->setObjectName(QStringLiteral("menuStart"));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        The_Game->setMenuBar(menubar);
        statusbar = new QStatusBar(The_Game);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        The_Game->setStatusBar(statusbar);

        menubar->addAction(menuStart->menuAction());
        menubar->addAction(menuOptions->menuAction());
        menubar->addAction(menuAbout->menuAction());

        retranslateUi(The_Game);

        QMetaObject::connectSlotsByName(The_Game);
    } // setupUi

    void retranslateUi(QMainWindow *The_Game)
    {
        The_Game->setWindowTitle(QApplication::translate("The_Game", "MainWindow", Q_NULLPTR));
        btn_switch_back->setText(QApplication::translate("The_Game", "\320\272_\320\237\321\200\320\265\320\264\321\213\320\263\321\200\320\265", Q_NULLPTR));
        menuStart->setTitle(QApplication::translate("The_Game", "Start", Q_NULLPTR));
        menuOptions->setTitle(QApplication::translate("The_Game", "Options", Q_NULLPTR));
        menuAbout->setTitle(QApplication::translate("The_Game", "About", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class The_Game: public Ui_The_Game {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THE_GAME_H
