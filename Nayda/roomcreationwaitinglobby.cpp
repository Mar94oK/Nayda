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
    setCurrentOpponentAwaiting(FIRST_OPPONENT_AWAITING);
    ui->lcd_BackCounter->setVisible(false);
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
     QString uiWaitingForOpponentsLobbyFilesLocation = "Munchkin/Nayda/Pictures/gameSettingsWidget";
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

void RoomCreationWaitingLobby::SetUpOpponentsName(QPushButton *btn, const QString &name)
{
    btn->setText(name);
}

bool RoomCreationWaitingLobby::CheckOpponentNameIsUnique(const QString &name)
{
    //Do not allow the server to involve clients with non-unique names;
    //instead sending each time the strings there might be a spcial identifier
    //sent for each client (ment opponent), so the game clients can distinguish them
    //from each other.
    //Nonetheless, nowadays it is doesn't matter whether it will be string or
    //a specified digit.
    //Count - 10 Rooms, 6 Clients each. 60 Sockets, 60 Strings.
    //Assume name not longer 13 Symbols.. Count.
    //But mark as expected improvement anyway.The first one I meant.
    //NAY-001:MARK_EXPECTED_IMPROVEMENT
    for (int var = 0; var < _opponentsNames.size(); ++var)
    {
        if (_opponentsNames[var] == name)
        {
            qDebug() << "NAY-001: Warning: Opponent's Name is not unique!";
            //return false;
        }
    }
    return true;
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
    if (_currentOpponentAwaiting == (_gameSettings.maximumNumberOfPlayers() - 1))
    {
        qDebug() << "NAY-001: Error while Opponent's entering! More then expected!";
        return;
    }

    if (_currentOpponentAwaiting < _opponnets.size())
    {
        if (CheckOpponentNameIsUnique(opponentName))
        {
            SetUpOpponentsName( _opponnets[_currentOpponentAwaiting], opponentName);
            _opponentsNames.push_back(opponentName);
            ++_currentOpponentAwaiting;
            if (_currentOpponentAwaiting == _opponnets.size())
                emit SignalAllThePlayersAreHere();
            return;
        }
        qDebug() << "NAY-001: Opponent's name is not unique! ";
    }
    else
    {
        qDebug() << "NAY-001: Error while Opponent's entering! More then expected! Incorrect opponents number IN GUI! Check GUI!";
        //NAY-001: MARK_EXPECTED_ERROR
        //this number - _opponnets.size() should be set with respect to maximum number of players allowed by the game!
        //so add gui buttons for them!
        //this ussue also true for The_Game itself.
        return;
    }
}

void RoomCreationWaitingLobby::SlotProcessRemoteHostClosedErrorReport()
{
    close();
}

void RoomCreationWaitingLobby::EnbleBackCounterToTheGameStart()
{
    ui->lcd_BackCounter->setVisible(true);
    _backCountTimer = new QTimer();
}

void RoomCreationWaitingLobby::SlotBackCounterSetNewValue(QString value)
{
    ui->lcd_BackCounter->display(value);
}

uint32_t RoomCreationWaitingLobby::currentOpponentAwaiting() const
{
    return _currentOpponentAwaiting;
}

void RoomCreationWaitingLobby::setCurrentOpponentAwaiting(const uint32_t &currentOpponentAwaiting)
{
    _currentOpponentAwaiting = currentOpponentAwaiting;
}
