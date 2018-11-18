#include "serverqueryoversizedwindow.h"
#include "ui_serverqueryoversizedwindow.h"
#include <QDebug>
#include <QStandardPaths>

ServerQueryOversizedWindow::ServerQueryOversizedWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerQueryOversizedWindow)
{
    ui->setupUi(this);
    ui->lbl_Text->setText(_serverQueueIversizedBaseText);
    SetUpPicturesAddresses();
    setUpButtonPicture(ui->btn_Picture, _serverQueueIversizedPictureAddress, buttonsWidthCoefficient, buttonsHeightWidthRelatio);

    QObject::connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &ServerQueryOversizedWindow::SlotUnlockUserButtonsAfterConnectionToRoomReply);
}

ServerQueryOversizedWindow::~ServerQueryOversizedWindow()
{
    delete ui;
}

void ServerQueryOversizedWindow::SetUpPicturesAddresses()
{
    qDebug() <<"NAY-0001: Application location: "<< QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
    QString homeDirectory = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);

#ifdef Q_OS_WIN
//NAY-001: MARK_EXPECTED_ERROR
     QString uiServerQueueOversizedFilesLocation = "Munchkin/Nayda/Pictures/serverQueueOversizedWindow";
     homeDirectory = "D:/";
#elif defined Q_OS_UNIX
     QString uiServerQueueOversizedFilesLocation = "Munchkin/Nayda/Nayda/Pictures/serverQueueOversizedWindow";
#endif

     QString picturesLocationBasis = homeDirectory + uiServerQueueOversizedFilesLocation + "/";

     _serverQueueIversizedPictureAddress = picturesLocationBasis + "pinguinsQueue.jpg";
}

void ServerQueryOversizedWindow::setUpButtonPicture(QPushButton * const btn, const QString &picturePath, double widthCoeff, double heightWidthRelatio)
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
    btn->setMaximumWidth(geometry().width()*widthCoeff);
    btn->setMaximumHeight(geometry().width()*widthCoeff*heightWidthRelatio);
    btn->setFlat(true);
    btn->setAutoFillBackground(true);
    btn->setPalette(plteBtnMainRepresenter);
}

void ServerQueryOversizedWindow::closeEvent(QCloseEvent *event)
{
    emit SignalUnlockUserButtonsAfterConnectionToRoomReply();
}
