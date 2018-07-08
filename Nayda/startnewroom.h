#ifndef START_NEW_ROOM_H
#define START_NEW_ROOM_H

#include <QWidget>
#include <QDebug>
#include <serversettings.h>
#include <Server/server.h>

namespace Ui {
class startNewRoom;
}

class startNewRoom : public QWidget
{
    Q_OBJECT

private:

    Ui::startNewRoom *ui;
    ServerSettings* serverSettingsWindow = nullptr;

    void closeEvent(QCloseEvent *event);

public:
    explicit startNewRoom(QWidget *parent = 0);
    ~startNewRoom();

signals:
    void sig_dbgBtnPlayWithDefaultsPressed(bool);
    void sig_userIsClosingStartNewRoomWindow(bool);
    void sig_userHaveChangedServerSettings(serverSettings settings);
    void sig_openRoomForConnection();
    void sig_sendTestDataToServer();

public slots:

    void slot_startGameWithDefaults(void);
    void slot_showServerSettings(void);
    void slot_userhaveChangedServerSetting(serverSettings settings);
    void slot_openRoomForConnection();
    void slot_sendTestDataToServer();

};

#endif // START_NEW_ROOM_H
