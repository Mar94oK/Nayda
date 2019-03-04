#include "roomcreationwaitinglobby.h"
#include "ui_roomcreationwaitinglobby.h"
#include "munchkinglobaldefines.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QStyle>

RoomCreationWaitingLobby::RoomCreationWaitingLobby(const GameSettings &settings, QWidget *parent) :
    _gameSettings(settings), QWidget(parent),
    ui(new Ui::RoomCreationWaitingLobby)
{
    ui->setupUi(this);
    SetUpPicturesAddressses();
    setCurrentOpponentAwaiting(FIRST_OPPONENT_AWAITING);
    ui->lcd_BackCounter->setVisible(false);
    ui->lbl_TimeLeftBeforeStart->setVisible(false);
    SetUpSignalsSlotsConnections();
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
//NAY-001: EXPECTED_ERROR
     QString uiWaitingForOpponentsLobbyFilesLocation = "Munchkin/Nayda/Pictures/waitingForOpponentsLobby";
     homeDirectory = "D:/";
#elif defined Q_OS_UNIX
     QString uiWaitingForOpponentsLobbyFilesLocation = "Munchkin/Nayda/Nayda/Pictures/waitingForOpponentsLobby";
#endif

     QString picturesLocationBasis = homeDirectory + uiWaitingForOpponentsLobbyFilesLocation + "/";

     _mainPlayerPictureAddress = picturesLocationBasis + "Crown.png";

}

void RoomCreationWaitingLobby::SetUpSignalsSlotsConnections()
{
    QObject::connect(this, &RoomCreationWaitingLobby::SignalChartMessageReceived, ui->widget, &MunchkinDialog::SlotShowMessage);
    QObject::connect(ui->widget, &MunchkinDialog::SignalSendMessage, this, &RoomCreationWaitingLobby::SlotProcessChartMessageSending);
}

void RoomCreationWaitingLobby::setUpButtonPicture(QPushButton * const btn, const QString &picturePath, double widthCoeff, double heightWidthRelatio)
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
    //btn->setMaximumWidth(geometry().width()*widthCoeff);
    //btn->setMaximumHeight(geometry().width()*widthCoeff*heightWidthRelatio);
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
    applyNewSettings(settings);
    setUpCreatorsName(settings.clientName());
    setUpButtonPicture(ui->btn_Creator, _mainPlayerPictureAddress, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    ui->wdgt_GameSettings->ApplyNewSettings(settings);
    ui->wdgt_GameSettings->setUpInitialState();

    //check how many opponents buttons to show
    switch (settings.maximumNumberOfPlayers())
    {
    //Debug - for only testing purposes
    case 2:
        ui->btn_Opponent_2->hide();
        ui->btn_Opponent_3->hide();
        ui->btn_Opponent_4->hide();
        ui->btn_Opponent_5->hide();
        _opponnets.push_back(ui->btn_Opponent_1);
    break;
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
            SetUpOpponentsName( _opponnets[_currentOpponentAwaiting], opponentName + " " + QString::number(_currentOpponentAwaiting + 1));
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
        //NAY-001: EXPECTED_ERROR
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

void RoomCreationWaitingLobby::SlotProcessServerReportsClientIsLeaving(const QString &name)
{
    //Find this name thrue opponent's names:
    for (uint32_t var = 0; var < _opponentsNames.size(); ++var)
    {
        if (_opponentsNames[var] == name)
        {
            _opponnets[var]->setText("Opponent " + QString::number(var+1));
            --_currentOpponentAwaiting;
            _opponentsNames.erase(_opponentsNames.begin() + var);
            qDebug() << "NAY-001: Deleted opponnet with name: " << name << " in postion " << var;
            return;
        }
    }

}

void RoomCreationWaitingLobby::SlotProcessServerReportsRoomHasChangedOwner(const QString &previousOwner, const QString &currentOwner)
{
    //Algorythm;
    //1. Change owner's name:
    setUpCreatorsName(currentOwner);
    //2. Clear the name of the opponent on wchin it was stend before;
    //3. Adjust all the other players names and replace them to the other buttons

    //Первый игрок - это мастер. Его не надо отражать в списке оппонентов.

    //А ещё требуется сбросить на единицу номер ожидающего оппонента -
    //т.к. по сути это тоже репорт об удалении клиента, только мастера.
    //Сервер не посылает сообщений "ушёл клиент" если ушёл мастер.
    //И сменился владелец комнаты
    --_currentOpponentAwaiting;

    for (uint32_t var = 0; var < _opponentsNames.size(); ++var)
    {
        qDebug() << "Names: " << _opponentsNames[var];
    }

    for (uint32_t var = 0; var < _opponentsNames.size(); ++var)
    {
        if (_opponentsNames[var] == currentOwner)
        {
            //rename new master
            qDebug() << "NAY-001: Renaming new master: ";
            _opponnets[var]->setText("Opponent " + QString::number(var + 1));
            //rename last
            _opponnets[_opponentsNames.size() - 1]->setText("Opponent " + QString::number(_opponentsNames.size()));
            //remember the size which opponentNames have had
            uint32_t sizeWas = _opponentsNames.size();
            //remove deleted (who has becoe master) and adjust names
            _opponentsNames.erase(_opponentsNames.begin() + var);
            if (var < sizeWas - 1)
            {
                //redraw all the names left.
                //1. define how many to redraw
                uint32_t upToRedraw = sizeWas - var - 1; // the last one will be simply renamed to "Opponent (number)"
                for (int y = 0; y < upToRedraw; ++y)
                {
                    try
                    {
                        _opponnets[var+y]->setText(_opponentsNames[var+y]);
                    }
                    catch (...)
                    {
                        qDebug() << "CATCH: ERROR While SlotProcessServerReportsRoomHasChangedOwner() ";
                    }
                }
            }
            return;
        }

    }
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

void RoomCreationWaitingLobby::SetUpForNotMasterPossessionType(const ServerClientWantedToEnterTheRoomReplyData &data)
{
    //1. Apply new settings:

    _gameSettings.applyNewSettings(data.providedSettings);
    setUpCreatorsName(data.masterName);
    setUpButtonPicture(ui->btn_Creator, _mainPlayerPictureAddress, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    ui->wdgt_GameSettings->ApplyNewSettings(data.providedSettings);
    ui->wdgt_GameSettings->setUpInitialState();

    //2. Check maximum number of players to disable unnecessary buttons;
    switch (data.providedSettings.maximumNumberOfPlayers())
    {
    case 2:
        ui->btn_Opponent_2->hide();
        ui->btn_Opponent_3->hide();
        ui->btn_Opponent_4->hide();
        ui->btn_Opponent_5->hide();
        _opponnets.push_back(ui->btn_Opponent_1);
    break;
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
        qDebug() << "NAY-001: number of player is set to " << data.providedSettings.maximumNumberOfPlayers() << " Too much. Rework the procedure!!!";
        break;
    }

    //3. SetUp Opponent's names (on Server's side it is necessary to add the player
    // too room just before this message was sent - to be sure he recieved the ID necessary):

    //check wheteher players size is equфl or less maximum number of opponents - 1 (1 - Leader)
    if (data.players.size() <= _gameSettings.maximumNumberOfPlayers())
    {
        qDebug() << "NAY-001: SetUpForNotMasterPossessionType() data.players.size() Size OK!";
    }
    else
    {
        qDebug() << "NAY-001: SetUpForNotMasterPossessionType() Eror While checking size";
        qDebug() << "NAY-001: data.players.size() > (_gameSettings.maximumNumberOfPlayers() - 1)";
        return;
    }

    qDebug() << "Players size: " << data.players.size();

    for (uint32_t var = 1; var < data.players.size(); ++var)
    {
        if (data.players[var].playerID != 0) //0 - first Player (Master ID)
        {
            _opponnets[var-1]->setText(data.players[var].playerName + " " + QString::number(data.players[var].playerID));
            //Add also to the _opponentsNames;
            //And DO NOT send Master connection form the server as OponnetIsEnetering.
            //It is an opponent, but should not be in the vector - vector of opponentNames is responsible only for
            //OPPONENTS
            _opponentsNames.push_back(data.players[var].playerName);
            ++_currentOpponentAwaiting;
        }
    }
}
