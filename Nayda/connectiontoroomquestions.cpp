#include "connectiontoroomquestions.h"
#include "ui_connectiontoroomquestions.h"
#include <QDebug>
#include <QStandardPaths>

ConnectionToRoomQuestions::ConnectionToRoomQuestions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionToRoomQuestions)
{
    ui->setupUi(this);
    SetUpPicturesAddresses();
    setUpButtonPicture(ui->pushButton, _QuestionPictureAddress, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    SetUpConnections();

    //NAY-001:MARK_EXPECTED_IMPROVEMENT
    //Not to disable these options, allowing user only to see them.
    ui->chckBox_AgreeToWait->setEnabled(false);
    ui->chckBox_AgreeToWait->setCheckState(Qt::CheckState::Checked);

    ui->chckBox_ConnectToAnyRoom->setEnabled(false);
    ui->chckBox_ConnectToAnyRoom->setCheckState(Qt::CheckState::Unchecked);

    _connectToAnyRoom = ui->chckBox_ConnectToAnyRoom->isChecked();
    _agreeToWait = ui->chckBox_AgreeToWait->isChecked();

    ui->pushButton->setEnabled(false);
}

ConnectionToRoomQuestions::~ConnectionToRoomQuestions()
{
    delete ui;
}

void ConnectionToRoomQuestions::SetUpPicturesAddresses()
{
    qDebug() <<"NAY-0001: Application location: "<< QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
    QString homeDirectory = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);

#ifdef Q_OS_WIN
//NAY-001: MARK_EXPECTED_ERROR
     QString uiConnectionToRoomQuestionsFilesLocation = "Munchkin/Nayda/Pictures/connectionToRoomQuestions";
     homeDirectory = "D:/";
#elif defined Q_OS_UNIX
     QString uiConnectionToRoomQuestionsFilesLocation = "Munchkin/Nayda/Nayda/Pictures/connectionToRoomQuestions";
#endif

     QString picturesLocationBasis = homeDirectory + uiConnectionToRoomQuestionsFilesLocation + "/";

     _QuestionPictureAddress = picturesLocationBasis + "QuestionMark.png";
}

void ConnectionToRoomQuestions::setUpButtonPicture(QPushButton * const btn, const QString &picturePath, double widthCoeff, double heightWidthRelatio)
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

void ConnectionToRoomQuestions::SetUpConnections()
{
    QObject::connect(ui->chckBox_AgreeToWait, &QCheckBox::clicked, this, &ConnectionToRoomQuestions::SlotChangedAgreeToWait);
    QObject::connect(ui->chckBox_ConnectToAnyRoom, &QCheckBox::clicked, this, &ConnectionToRoomQuestions::SlotChangedConnectionToAnyRoom);
    QObject::connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &ConnectionToRoomQuestions::SlotSendClientConnectionToRoomRequest);
}

void ConnectionToRoomQuestions::SlotChangedConnectionToAnyRoom(bool value)
{
    _connectToAnyRoom = value;
}

void ConnectionToRoomQuestions::SlotChangedAgreeToWait(bool value)
{
    _agreeToWait = value;
}

void ConnectionToRoomQuestions::SlotSendClientConnectionToRoomRequest()
{
    qDebug() << "NAY-001: Sending signal from Questions Dialog: ";
    emit SignalSendClientConnectionToRoomRequest(ClientConnectToRoomSettingsData(_agreeToWait, _connectToAnyRoom));
}
