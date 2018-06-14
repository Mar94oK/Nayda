#ifndef START_NEW_ROOM_H
#define START_NEW_ROOM_H

#include <QWidget>
#include <QDebug>
#include <serversettings.h>

namespace Ui {
class startNewRoom;
}

class start_new_room : public QWidget
{
    Q_OBJECT

public:
    explicit start_new_room(QWidget *parent = 0);
    ~start_new_room();

signals:
    void dbgBtnPlayWithDefaultsPressed(bool);
    void userIsClosingStartNewRoomWindow(bool);

public slots:

    void startGameWithDefaults(void);
    void showServerSettings(void);


private:
    Ui::startNewRoom *ui;
    //ServerSettings*

    void closeEvent(QCloseEvent *event);
};

#endif // START_NEW_ROOM_H
