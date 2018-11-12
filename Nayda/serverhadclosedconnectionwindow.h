#ifndef SERVERHADCLOSEDCONNECTIONWINDOW_H
#define SERVERHADCLOSEDCONNECTIONWINDOW_H

#include <QDialog>
#include <QString>
#include <QStandardPaths>

namespace Ui {
class ServerHadClosedConnectionWindow;
}

class ServerHadClosedConnectionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ServerHadClosedConnectionWindow(QWidget *parent = 0);
    ~ServerHadClosedConnectionWindow();

private:
    Ui::ServerHadClosedConnectionWindow *ui;

private:

    QString _serverClosedPictureAddress;
    QString _serverHadClosedConnectionBaseText = "Уууупс. Кажется, сервер разорвал соединение./n"
                                                 "Попробуйте подключиться снова!";
    const double buttonsWidthCoefficient = 0.1;
    const double buttonsHeightWidthRelatio = 1.0000;



private:

    void SetUpPicturesAddresses();
    void setUpButtonPicture(QPushButton* const btn, const QString& picturePath, double widthCoeff, double heightWidthRelatio);

};

#endif // SERVERHADCLOSEDCONNECTIONWINDOW_H
