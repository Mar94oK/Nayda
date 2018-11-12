#include "roomcreationwaitinglobby.h"
#include "ui_roomcreationwaitinglobby.h"
#include "munchkinglobaldefines.h"
#include <QDesktopWidget>
#include <QDebug>

RoomCreationWaitingLobby::RoomCreationWaitingLobby(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomCreationWaitingLobby)
{
    ui->setupUi(this);
    SetUpPicturesAddressses();
}

RoomCreationWaitingLobby::~RoomCreationWaitingLobby()
{
    delete ui;
}

void RoomCreationWaitingLobby::closeEvent(QCloseEvent *event)
{
    emit SignalUserIsClosingRoomCreationLobby();
}

void RoomCreationWaitingLobby::setUpUiGeometricRelations()
{
    QRect HwScreenSize = QApplication::desktop()->screenGeometry();
    int HwScreenSizeWidth = HwScreenSize.width();
    int HwScreenSizeHeight = HwScreenSize.height();

    setGeometry(0,0,
                static_cast<uint32_t> (HwScreenSizeWidth * GeometricLimitations::beforeTheGameWindowsSize),
                static_cast<uint32_t> (HwScreenSizeHeight * GeometricLimitations::beforeTheGameWindowsSize));

    setGeometry(QStyle::alignedRect(Qt::LeftToRight,
                                    Qt::AlignCenter,
                                    size(),
                                    QApplication::desktop()->availableGeometry()));
}

void RoomCreationWaitingLobby::applyNewSettings(GameSettings settings)
{
    _gameSettings.applyNewSettings(settings);
}

void RoomCreationWaitingLobby::setUpCreatorsName(const QString &name)
{
    ui->btn_Creator->setText(name);
}

void RoomCreationWaitingLobby::SetUpPicturesAddressses()
{
    qDebug() <<"NAY-0001: Application location: "<< QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
    QString homeDirectory = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);

#ifdef Q_OS_WIN
//NAY-001: MARK_EXPECTED_ERROR
     QString uiPlayMenuFilesLocation = "Munchkin/Nayda/Pictures/gameSettingsWidget";
     homeDirectory = "D:/";
#elif defined Q_OS_UNIX
     QString uiWaitingForOpponentsLobbyFilesLocation = "Munchkin/Nayda/Nayda/Pictures/waitingForOpponentsLobby";
#endif

     QString picturesLocationBasis = homeDirectory + uiWaitingForOpponentsLobbyFilesLocation + "/";

     _mainPlayerPictureAddress = picturesLocationBasis + "Crown.png";

}

void RoomCreationWaitingLobby::setUpButtonPicture(QPushButton * const btn, const QString &picturePath, double widthCoeff, double heightWidthRelatio)
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

void RoomCreationWaitingLobby::SetUpInitalState(GameSettings settings)
{
    _gameSettings.applyNewSettings(settings);
    setUpCreatorsName(settings.clientName());
    setUpButtonPicture(ui->btn_Creator, _mainPlayerPictureAddress, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    ui->wdgt_GameSettings->ApplyNewSettings(settings);
    ui->wdgt_GameSettings->setUpInitialState();

    //check how many opponents buttons to show
    switch (settings.maximumNumberOfPlayers())
    {
    case 3:
        ui->btn_Opponent_3->hide();
        ui->btn_Opponent_4->hide();
        ui->btn_Opponent_5->hide();
        _opponnets.push_back(ui->btn_Opponent_1);
        _opponnets.push_back(ui->btn_Opponent_2);
    break;
    case 4:
        ui->btn_Opponent_4->hide();
        ui->btn_Opponent_5->hide();
        _opponnets.push_back(ui->btn_Opponent_1);
        _opponnets.push_back(ui->btn_Opponent_2);
        _opponnets.push_back(ui->btn_Opponent_3);
        break;
    case 5:
        ui->btn_Opponent_5->hide();
        _opponnets.push_back(ui->btn_Opponent_1);
        _opponnets.push_back(ui->btn_Opponent_2);
        _opponnets.push_back(ui->btn_Opponent_3);
        _opponnets.push_back(ui->btn_Opponent_4);
        break;
    case 6:
        _opponnets.push_back(ui->btn_Opponent_1);
        _opponnets.push_back(ui->btn_Opponent_2);
        _opponnets.push_back(ui->btn_Opponent_3);
        _opponnets.push_back(ui->btn_Opponent_4);
        _opponnets.push_back(ui->btn_Opponent_5);
        break;
    default:
        qDebug() << "NAY-001: number of player is set to " << settings.maximumNumberOfPlayers() << " Too much. Rework the procedure!!!";
        break;
    }

}

void RoomCreationWaitingLobby::SlotProcessServerReportsOpponentIsEnteringRoom(const QString &opponentName)
{

}

void RoomCreationWaitingLobby::SlotProcessRemoteHostClosedErrorReport()
{
    close();
}
