#ifndef START_NEW_ROOM_H
#define START_NEW_ROOM_H

#include <QWidget>
#include <QDebug>
#include <serversettings.h>
#include <Server/server.h>

namespace Ui {
class startNewRoom;
}

class playMenu : public QWidget
{
    Q_OBJECT

private:

    Ui::startNewRoom *ui;
    ServerSettings* serverSettingsWindow = nullptr;
    void closeEvent(QCloseEvent *event);

public:

    explicit playMenu(QWidget *parent = 0);
    ~playMenu();

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

private:

    void setUpGeometricRelations();
    void setUpSignalsSlotsConnections();

};

#endif // START_NEW_ROOM_H
