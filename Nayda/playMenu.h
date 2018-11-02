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

public:

    explicit playMenu(QWidget *parent = 0);
    ~playMenu();

signals:

    void sig_dbgBtnPlayWithDefaultsPressed(bool);
    void sig_userIsClosingStartNewRoomWindow(bool);
    void sig_userHaveChangedServerSettings(serverSettings settings);
    void sig_openRoomForConnection();
    void sig_sendTestDataToServer();

private slots:



public slots:

    void slot_startGameWithDefaults(void);
    void slot_showServerSettings(void);
    void slot_userhaveChangedServerSetting(serverSettings settings);
    void slot_openRoomForConnection();
    void slot_sendTestDataToServer();

private:

    void setUpUiGeometricRelations();
    void setUpSignalsSlotsConnections();
    void setUpUiPicturesAddresses();
    void setUpButtonPicture(QPushButton* const btn, const QString& picturePath, double widthCoeff, double heightWidthRelatio);
    void setUpUiVisualizationParameters();
};

#endif // START_NEW_ROOM_H
