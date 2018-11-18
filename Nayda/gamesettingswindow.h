#ifndef GAMESETTINGSWINDOW_H
#define GAMESETTINGSWINDOW_H

#include <QDialog>
#include "gamesettings.h"

namespace Ui {
class GameSettingsWindow;
}

class GameSettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameSettingsWindow(GameSettings settings, QWidget *parent = 0);
    ~GameSettingsWindow();

private:
    Ui::GameSettingsWindow *ui;

private:
    GameSettings _gameSettings;
    void SignalsSlotsConnector();
    void SetupInitialAllowedFeatures();

private slots:

    void SlotUserHaveChangedMaximumNumberOfPlayers(unsigned int val);
    void SlotUserHaveChangedTotalTimeToMove(int val);
    void SlotUserHaveChangedTimeToThink(unsigned int val);
    void SlotUserHaveChangedTimeForOpponentsDecision(unsigned int val);
    void SlotUserHaveChangedDiplomacyTime(unsigned int val);
    void SlotUserHaveChangedHasAddonClericalErrors(bool has);
    void SlotUserHaveChangedHasAddonWildAxe(bool has);
    void SlotUserHaveChangedClientName(const QString& clientName);
    void SlotUserHaveChangedRoomName(const QString& roomName);
    void SlotUserHaveChangedRulesType(int automatic);
    void SlotUserHaveChangedSettingsChangesAllowance(bool);
    void SlotUserApplyedChangedSettings(bool);
    void SlotUserRejectedChangedSettings(bool);


private:

    QString _DiplomacyTimeBaseText = "Время, отведённое для дипломатии: ";
    QString _TimeForOpponentsDecisionBaseText = "Время, отведённое для раздумий оппонентов: ";
    QString _TimeToThinkBaseText = "Время отведённое на размышления: ";
    QString _MaximumNumberOfPLayersBaseText = "Максимальное количество игроков: ";
    QString _RulesTypeBaseText = "Тип правил: ";
    QString _TotalTimeToMoveBaseText = "Время, отведённое на ход: ";
    QString _UserNameBaseText = "Имя пользователя: ";
    QString _RoomNameBaseText = "Имя комнаты: ";
    QString _HasAddonWildAxeBaseText = "Дополнение Дикий Топор: ";
    QString _HasAddonClericalErrorsBaseText = "Дополнение Клирические Ошибки: ";
    QString _SettingsChangesBaseText = "Изменение настроек в процессе подготовки к игре: ";

signals:

    void SignalUserHaveChangedSettings(const GameSettings& settings);

};

#endif // GAMESETTINGSWINDOW_H
