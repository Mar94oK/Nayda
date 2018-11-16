#ifndef CONNECTIONTOROOMREJECTEDMESSAGEWINDOW_H
#define CONNECTIONTOROOMREJECTEDMESSAGEWINDOW_H

#include <QDialog>
#include <QString>


namespace Ui {
class ConnectionToRoomRejectedMessageWindow;
}

class ConnectionToRoomRejectedMessageWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionToRoomRejectedMessageWindow(QWidget *parent = 0);
    ~ConnectionToRoomRejectedMessageWindow();

private:
    Ui::ConnectionToRoomRejectedMessageWindow *ui;

private:

    QString _connectionToRoomRejectedPictureAddress;
    QString _connectionToRoomRejectedBaseText = "Вход воспрещён за отсутствием свободных комнат.\n"
                                                "Поставьте флаг \"Ждать подключения\" и \n"
                                                "повторите попытку! ";
    const double buttonsWidthCoefficient = 0.3;
    const double buttonsHeightWidthRelatio = 1.0000;


private:

    void SetUpPicturesAddresses();
    void setUpButtonPicture(QPushButton* const btn, const QString& picturePath, double widthCoeff, double heightWidthRelatio);

public:

    void SetText(bool noRooms);

};

#endif // CONNECTIONTOROOMREJECTEDMESSAGEWINDOW_H
