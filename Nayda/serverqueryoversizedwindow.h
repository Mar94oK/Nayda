#ifndef SERVERQUERYOVERSIZEDWINDOW_H
#define SERVERQUERYOVERSIZEDWINDOW_H

#include <QDialog>

namespace Ui {
class ServerQueryOversizedWindow;
}

class ServerQueryOversizedWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ServerQueryOversizedWindow(QWidget *parent = 0);
    ~ServerQueryOversizedWindow();

private:
    Ui::ServerQueryOversizedWindow *ui;

private:

    QString _serverQueueIversizedPictureAddress;
    QString _serverQueueIversizedBaseText = "Извините, но очередь на сервере переполнена. Попробуйте подключиться позднее!";
    const double buttonsWidthCoefficient = 0.3;
    const double buttonsHeightWidthRelatio = 1.0000;

private:

    void SetUpPicturesAddresses();
    void setUpButtonPicture(QPushButton* const btn, const QString& picturePath, double widthCoeff, double heightWidthRelatio);

    void closeEvent(QCloseEvent *event);

signals:

    void SignalUnlockUserButtonsAfterConnectionToRoomReply();

public slots:

    void SlotUnlockUserButtonsAfterConnectionToRoomReply() { emit SignalUnlockUserButtonsAfterConnectionToRoomReply();}

};

#endif // SERVERQUERYOVERSIZEDWINDOW_H
