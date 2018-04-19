#ifndef START_NEW_ROOM_H
#define START_NEW_ROOM_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class start_new_room;
}

class start_new_room : public QWidget
{
    Q_OBJECT

public:
    explicit start_new_room(QWidget *parent = 0);
    ~start_new_room();

signals:

    void dbg_btn_play_with_defaults_pressed(bool);
    void userIsClosingStartNewRoomWindow(bool);

public slots:

    void start_game_with_defaults(void);


private:
    Ui::start_new_room *ui;

    void closeEvent(QCloseEvent *event);
};

#endif // START_NEW_ROOM_H
