#ifndef START_NEW_ROOM_H
#define START_NEW_ROOM_H

#include <QWidget>
#include <QDebug>
#include <serversettings.h>
#include <Server/server.h>
#include <gamesettingswindow.h>
#include <gamesettings.h>
#include <MessagesDefinitions.h>

namespace Ui {
class startNewRoom;
}

enum class ConnectionState { NoServerSettingsProvided,
                             CompleteServerSettings,
                             Connection,
                             ConnectionTimeout };

class playMenu : public QWidget
{
    Q_OBJECT

private:

    Ui::startNewRoom *ui;
    ServerSettings* serverSettingsWindow = nullptr;
    GameSettingsWindow* gameSettingsWindow = nullptr;
    void closeEvent(QCloseEvent *event);

    QString _gameSettingsButtonPictureAddressDefault;
    QString _gameSettingsButtonPictureAddressSetUp;

    QString _connectionButtonPictureAddressDefault;
    QString _connectionButtonPictureAddressSetUp;
    QString _connectionButtonPictureAddressConnected;

    QString _createRoomButtonPictureAddressDefault;
    QString _createRoomButtonPictureAddressAllowed;

    QString _joinRoomButtonPictureAddressDefault;
    QString _joinRoomButtonPictureAddressAllowed;

    std::vector<QPushButton*> _uiButtons;

private:

    const double buttonsWidthCoefficient = 0.2;
    const double buttonsHeightWidthRelatio = 0.66;

private:

    ConnectionState _connectionState;
    GameSettings    _gameSettings;
    serverSettings  _serverSettings;

public:

    explicit playMenu(QWidget *parent = 0);
    ~playMenu();

signals:

    void sig_dbgBtnPlayWithDefaultsPressed(bool);
    void sig_userIsClosingStartNewRoomWindow(bool);
    void sig_userHaveChangedServerSettings(serverSettings settings);
    void sig_openRoomForConnection();
    void sig_sendTestDataToServer();

    void SignalUserHaveChangedGameSettings(const GameSettings&);

private slots:

public slots:

    void slot_startGameWithDefaults(void);
    void slot_showServerSettings(void);
    void slot_userHaveChangedServerSettings(serverSettings settings);
    void slot_openRoomForConnection();
    void slot_sendTestDataToServer();
    void SlotShowGameSettingsWindow();
    void SlotUserHaveChangedGameSettings(const GameSettings& settings);

    void SlotProcessServerQueryReplyData(ServerQueryReplyData data);

private:

    void setUpUiGeometricRelations();
    void setUpSignalsSlotsConnections();
    void setUpUiPicturesAddresses();
    void setUpButtonPicture(QPushButton* const btn, const QString& picturePath, double widthCoeff, double heightWidthRelatio);
    void setUpUiVisualizationParameters();
    void SetUpInitilButtonsStates();
};

#endif // START_NEW_ROOM_H
