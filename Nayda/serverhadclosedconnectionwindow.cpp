#include "serverhadclosedconnectionwindow.h"
#include "ui_serverhadclosedconnectionwindow.h"
#include <QDebug>

ServerHadClosedConnectionWindow::ServerHadClosedConnectionWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerHadClosedConnectionWindow)
{
    ui->setupUi(this);
    SetUpPicturesAddresses();
    setUpButtonPicture(ui->btnServeClosedPicture, _serverClosedPictureAddress, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    ui->btnServeClosedPicture->setEnabled(false);
    ui->label->setText(_serverHadClosedConnectionBaseText);
}

ServerHadClosedConnectionWindow::~ServerHadClosedConnectionWindow()
{
    delete ui;
}

void ServerHadClosedConnectionWindow::setUpButtonPicture(QPushButton * const btn, const QString &picturePath, double widthCoeff, double heightWidthRelatio)
{
    QPixmap pxmpBtnMainRepresenter(picturePath);
    QPalette plteBtnMainRepresenter(btn->palette());
    plteBtnMainRepresenter.setBrush(QPalette::Button,
                                    QBrush(pxmpBtnMainRepresenter.scaled(geometry().width()*widthCoeff,
                                            geometry().width()*widthCoeff*heightWidthRelatio,
                                            Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    qDebug() << "Size width picture: " << geometry().width()*widthCoeff;
    qDebug() << "Size height picture: " << geometry().width()*widthCoeff*heightWidthRelatio;


    btn->setMinimumWidth(geometry().width()*widthCoeff);
    btn->setMinimumHeight(geometry().width()*widthCoeff*heightWidthRelatio);
    btn->setFlat(true);
    btn->setAutoFillBackground(true);
    btn->setPalette(plteBtnMainRepresenter);
}

void ServerHadClosedConnectionWindow::SetUpPicturesAddresses()
{
    qDebug() <<"NAY-0001: Application location: "<< QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
    QString homeDirectory = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);

#ifdef Q_OS_WIN
//NAY-001: MARK_EXPECTED_ERROR
     QString uiPlayMenuFilesLocation = "Munchkin/Nayda/Pictures/gameSettingsWidget";
     homeDirectory = "D:/";
#elif defined Q_OS_UNIX
     QString uiServerHadClosedConnectionFilesLocation = "Munchkin/Nayda/Nayda/Pictures/serverHadClosedConnectionWindow";
#endif

     QString picturesLocationBasis = homeDirectory + uiServerHadClosedConnectionFilesLocation + "/";

     _serverClosedPictureAddress = picturesLocationBasis + "Closed.png";
}
