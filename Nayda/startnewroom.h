#ifndef START_NEW_ROOM_H
#define START_NEW_ROOM_H

#include <QWidget>
#include <QDebug>
#include <serversettings.h>

namespace Ui {
class startNewRoom;
}

class startNewRoom : public QWidget
{
    Q_OBJECT

private:

    Ui::startNewRoom *ui;
    ServerSettings* serverSettings = nullptr;

    void closeEvent(QCloseEvent *event);

public:
    explicit startNewRoom(QWidget *parent = 0);
    ~startNewRoom();

signals:
    void dbgBtnPlayWithDefaultsPressed(bool);
    void userIsClosingStartNewRoomWindow(bool);

public slots:

    void startGameWithDefaults(void);
    void showServerSettings(void);

};

#endif // START_NEW_ROOM_H
