#ifndef GAMESETTINGSWIDGET_H
#define GAMESETTINGSWIDGET_H

#include <QWidget>
#include "gamesettings.h"
#include <QString>
#include <QStandardPaths>
#include <QPushButton>


namespace Ui {
class GameSettingsWidget;
}

class GameSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameSettingsWidget(QWidget *parent = 0);
    ~GameSettingsWidget();

private:
    Ui::GameSettingsWidget *ui;

private:

    GameSettings _gameSettings;

public:

    void ApplyNewSettings(GameSettings settings);


private:

    QString _diplomacyTimerPictureAddress;
    QString _timeToWaitTimerPictureAddress;
    QString _timeToMoveTimerPictureAddress;
    QString _timeToThinkTimerPictureAddress;
    QString _timeForOpponentsToDecideTimerPictureAddress;
    QString _automaticRulesTypePictureAddress;
    QString _manualRulesTypePictureAddress;

    const double buttonsWidthCoefficient = 0.3;
    const double buttonsHeightWidthRelatio = 1.24633;

    QString _DiplomacyTimeBaseText = "Время, отведённое для дипломатии: ";
    QString _TimeForOpponentsDecisionBaseText = "Время, отведённое для раздумий оппонентов: ";
    QString _TimeToThinkBaseText = "Время отведённое на размышления: ";
    QString _MaximumNumberOfPLayersBaseText = "Максимальное количество игроков: ";
    QString _RulesTypeBaseText = "Тип правил: ";
    QString _TotalTimeToMoveBaseText = "Время, отведённое на ход: ";
    QString _UserNameBaseText = "Имя пользователя: ";
    QString _HasAddonWildAxeBaseText = "Дополнение Дикий Топор: ";
    QString _HasAddonClericalErrorsBaseText = "Дополнение Клирические Ошибки: ";
    QString _SettingsChangesBaseText = "Изменение настроек в процессе подготовки к игре: ";

public:

    void setUpInitialState();

private:

    void setUpUiPicturesAddresses();
    void setUpButtonPicture(QPushButton* const btn, const QString& picturePath, double widthCoeff, double heightWidthRelatio);


};

#endif // GAMESETTINGSWIDGET_H
