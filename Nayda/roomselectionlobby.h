#ifndef ROOMSELECTIONLOBBY_H
#define ROOMSELECTIONLOBBY_H

#include <QDialog>

namespace Ui {
class RoomSelectionLobby;
}

class RoomSelectionLobby : public QDialog
{
    Q_OBJECT

public:
    explicit RoomSelectionLobby(QWidget *parent = 0);
    ~RoomSelectionLobby();

private:
    Ui::RoomSelectionLobby *ui;
};

#endif // ROOMSELECTIONLOBBY_H
