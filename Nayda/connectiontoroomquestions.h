#ifndef CONNECTIONTOROOMQUESTIONS_H
#define CONNECTIONTOROOMQUESTIONS_H

#include <QDialog>
#include "MessagesDefinitions.h"

namespace Ui {
class ConnectionToRoomQuestions;
}

class ConnectionToRoomQuestions : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionToRoomQuestions(QWidget *parent = 0);
    ~ConnectionToRoomQuestions();

private:
    Ui::ConnectionToRoomQuestions *ui;


private:

    QString _QuestionPictureAddress;
    QString _roomConnectionQuestionBaseText = "Уууупс. Кажется, сервер разорвал соединение.\n"
                                                 "Попробуйте подключиться снова!";
    const double buttonsWidthCoefficient = 0.3;
    const double buttonsHeightWidthRelatio = 1.0000;

private:

    void SetUpPicturesAddresses();
    void setUpButtonPicture(QPushButton* const btn, const QString& picturePath, double widthCoeff, double heightWidthRelatio);

    void SetUpConnections();

private:

    bool _agreeToWait = false;
    bool _connectToAnyRoom = false;


private slots:

    void SlotChangedConnectionToAnyRoom(bool value);
    void SlotChangedAgreeToWait(bool value);
    void SlotSendClientConnectionToRoomRequest();

signals:

    void SignalSendClientConnectionToRoomRequest(ClientConnectToRoomSettingsData data);

};

#endif // CONNECTIONTOROOMQUESTIONS_H
