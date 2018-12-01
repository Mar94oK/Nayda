#include "gamesettingswidget.h"
#include "ui_gamesettingswidget.h"
#include <QDebug>

GameSettingsWidget::GameSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameSettingsWidget)
{
    ui->setupUi(this);

    setUpUiPicturesAddresses();
}

GameSettingsWidget::~GameSettingsWidget()
{
    delete ui;
}

void GameSettingsWidget::ApplyNewSettings(GameSettings settings)
{
    _gameSettings.applyNewSettings(settings);
}

void GameSettingsWidget::setUpUiPicturesAddresses()
{
    qDebug() <<"NAY-0001: Application location: "<< QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
    QString homeDirectory = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);

#ifdef Q_OS_WIN
//NAY-001: MARK_EXPECTED_ERROR
     QString uiPlayMenuFilesLocation = "Munchkin/Nayda/Pictures/gameSettingsWidget";
     homeDirectory = "D:/";
#elif defined Q_OS_UNIX
     QString uiPlayMenuFilesLocation = "Munchkin/Nayda/Nayda/Pictures/gameSettingsWidget";
#endif

     QString picturesLocationBasis = homeDirectory + uiPlayMenuFilesLocation + "/";

     _diplomacyTimerPictureAddress = picturesLocationBasis + "DiplomacyTime.png";
     _timeToMoveTimerPictureAddress = picturesLocationBasis + "TimeToMove.png";
     _timeToThinkTimerPictureAddress = picturesLocationBasis + "TimeToThink.png";
     _timeForOpponentsToDecideTimerPictureAddress = picturesLocationBasis + "TimeForOpponentsDecision.png";
     _automaticRulesTypePictureAddress = picturesLocationBasis + "AutomaticRuleType.png";
     _manualRulesTypePictureAddress = picturesLocationBasis + "ManualRulesType.png";
     _totalNumberOfPeoplePictureAddress = picturesLocationBasis + "NumberOfPeople.png";
     _hasAddonWildAxePictureAddress = picturesLocationBasis + "WildAxeAddon.png";
     _hasAddonClericalErrorsPictureAddress = picturesLocationBasis + "ClericalErrorsAddon.png";
}

void GameSettingsWidget::setUpInitialState()
{
    setUpButtonPicture(ui->btn_DiplomacyTime, _diplomacyTimerPictureAddress, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    setUpButtonPicture(ui->btn_TimeForOpponentsDecision, _timeForOpponentsToDecideTimerPictureAddress, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    setUpButtonPicture(ui->btn_TimeToMove, _timeToMoveTimerPictureAddress, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    setUpButtonPicture(ui->btn_TimeToThink, _timeToThinkTimerPictureAddress, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    setUpButtonPicture(ui->btn_RulesType, _automaticRulesTypePictureAddress, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    setUpButtonPicture(ui->btn_MaxNumberOfPlayers, _totalNumberOfPeoplePictureAddress, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    setUpButtonPicture(ui->btn_HasAddonWildAxe, _hasAddonWildAxePictureAddress, buttonsWidthCoefficient, buttonsHeightWidthRelatio);
    setUpButtonPicture(ui->btn_HasAddonClericalErrors, _hasAddonClericalErrorsPictureAddress, buttonsWidthCoefficient, buttonsHeightWidthRelatio);

    ui->btn_DiplomacyTime->setText("");
    ui->btn_TimeToMove->setText("");
    ui->btn_TimeForOpponentsDecision->setText("");
    ui->btn_TimeToThink->setText("");
    ui->btn_RulesType->setText("");
    ui->btn_MaxNumberOfPlayers->setText("");
    ui->btn_HasAddonWildAxe->setText("");
    ui->btn_HasAddonClericalErrors->setText("");


    ui->lbl_DiplomacyTime->setText(_DiplomacyTimeBaseText + QString::number(_gameSettings.diplomacyTime()) + " секунд.");
    ui->lbl_TimeForOpponentsDecision->setText(_TimeForOpponentsDecisionBaseText + QString::number(_gameSettings.timeForOpponentsDecision()) + " секунд.");
    ui->lbl_TimeToThink->setText(_TimeToThinkBaseText + QString::number(_gameSettings.timeToThink()) + " секунд.");
    switch (_gameSettings.maximumNumberOfPlayers())
    {
    case 3:
    case 4:
        ui->lbl_MaximumNumberOfPlayers->setText(_MaximumNumberOfPLayersBaseText + QString::number(_gameSettings.maximumNumberOfPlayers()) + " игрока.");
        break;
    default:
        ui->lbl_MaximumNumberOfPlayers->setText(_MaximumNumberOfPLayersBaseText + QString::number(_gameSettings.maximumNumberOfPlayers()) + " игроков.");
        break;
    }
    ui->lbl_RulesType->setText(_RulesTypeBaseText + (_gameSettings.rulesType() == RulesType::Automatic ? "Автоматические." : "Ручные!"));
    ui->lbl_TimeToMove->setText(_TotalTimeToMoveBaseText +QString::number(_gameSettings.totalTimeToMove()) + " секунд.");
    ui->lbl_HasAddonWildAxe->setText(_HasAddonWildAxeBaseText + (_gameSettings.hasAddonWildAxe() ? "используется." : "отключен."));
    ui->lbl_HasAddonClericalErrors->setText(_HasAddonClericalErrorsBaseText + (_gameSettings.hasAddonClericalErrors() ? "используется." : "отключен."));


    if (_gameSettings.settingsCorrectionAllowed())
    {
        qDebug() << "NAY-001: Settings changing allowed!";
    }
}

void GameSettingsWidget::setUpButtonPicture(QPushButton * const btn, const QString &picturePath, double widthCoeff, double heightWidthRelatio)
{
    QPixmap pxmpBtnMainRepresenter(picturePath);
    QPalette plteBtnMainRepresenter(btn->palette());
    plteBtnMainRepresenter.setBrush(QPalette::Button,
                                    QBrush(pxmpBtnMainRepresenter.scaled(geometry().width()*widthCoeff,
                                            geometry().width()*widthCoeff*heightWidthRelatio,
                                            Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    btn->setMinimumWidth(geometry().width()*widthCoeff);
    btn->setMinimumHeight(geometry().width()*widthCoeff*heightWidthRelatio);
    btn->setMaximumWidth(geometry().width()*widthCoeff);
    btn->setMaximumHeight(geometry().width()*widthCoeff*heightWidthRelatio);
    btn->setFlat(true);
    btn->setAutoFillBackground(true);
    btn->setPalette(plteBtnMainRepresenter);
}
