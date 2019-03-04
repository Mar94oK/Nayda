#include "connectiontoroomrejectedmessagewindow.h"
#include "ui_connectiontoroomrejectedmessagewindow.h"
#include <QPixmap>
#include <QDebug>
#include <QStandardPaths>

ConnectionToRoomRejectedMessageWindow::ConnectionToRoomRejectedMessageWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionToRoomRejectedMessageWindow)
{
    ui->setupUi(this);
    SetUpPicturesAddresses();
    setUpButtonPicture(ui->btn_Rejected, _connectionToRoomRejectedPictureAddress, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
}

ConnectionToRoomRejectedMessageWindow::~ConnectionToRoomRejectedMessageWindow()
{
    delete ui;
}

void ConnectionToRoomRejectedMessageWindow::SetUpPicturesAddresses()
{
    qDebug() <<"NAY-0001: Application location: "<< QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
    QString homeDirectory = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);

#ifdef Q_OS_WIN
//NAY-001: EXPECTED_ERROR
     QString uiConnectionToRoomRejectedFilesLocation = "Munchkin/Nayda/Pictures/gameSettingsWidget";
     homeDirectory = "D:/";
#elif defined Q_OS_UNIX
     QString uiConnectionToRoomRejectedFilesLocation = "Munchkin/Nayda/Nayda/Pictures/connectionToRoomRejectedWindow";
#endif

     QString picturesLocationBasis = homeDirectory + uiConnectionToRoomRejectedFilesLocation + "/";

     _connectionToRoomRejectedPictureAddress = picturesLocationBasis + "EnranceRestricted.png";

}

void ConnectionToRoomRejectedMessageWindow::setUpButtonPicture(QPushButton * const btn, const QString &picturePath, double widthCoeff, double heightWidthRelatio)
{


    QPixmap pxmpBtnMainRepresenter(picturePath);
    QPalette plteBtnMainRepresenter(btn->palette());
    plteBtnMainRepresenter.setBrush(QPalette::Button,
                                    QBrush(pxmpBtnMainRepresenter.scaled(geometry().width()*widthCoeff,
                                            geometry().width()*widthCoeff*heightWidthRelatio,
                                            Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    //qDebug() << "Size width picture: " << geometry().width()*widthCoeff;
    //qDebug() << "Size height picture: " << geometry().width()*widthCoeff*heightWidthRelatio;


    btn->setMinimumWidth(geometry().width()*widthCoeff);
    btn->setMinimumHeight(geometry().width()*widthCoeff*heightWidthRelatio);
    btn->setFlat(true);
    btn->setAutoFillBackground(true);
    btn->setPalette(plteBtnMainRepresenter);
}

void ConnectionToRoomRejectedMessageWindow::SetText(bool noRooms)
{
    if (noRooms)
        ui->lbl_Text->setText(_connectionToRoomRejectedBaseText);
    else
        ui->lbl_Text->setText("Вход невозможен!");
}
