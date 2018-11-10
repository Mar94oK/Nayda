#include "gamesettingswindow.h"
#include "ui_gamesettingswindow.h"
#include <QSpinBox>
#include <QPushButton>

GameSettingsWindow::GameSettingsWindow(GameSettings settings, QWidget *parent) :
    _gameSettings(settings), QDialog(parent),
    ui(new Ui::GameSettingsWindow)
{
    ui->setupUi(this);
    SetupInitialAllowedFeatures();
    SignalsSlotsConnector();
}

GameSettingsWindow::~GameSettingsWindow()
{
    delete ui;
}

void GameSettingsWindow::SignalsSlotsConnector()
{
    QObject::connect(ui->spBox_TotalTimeToMove, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &GameSettingsWindow::SlotUserHaveChangedTotalTimeToMove);
    QObject::connect(ui->spBox_DiplomacyTime, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &GameSettingsWindow::SlotUserHaveChangedDiplomacyTime);
    QObject::connect(ui->spBox_MaximumNumberOfPlayers, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &GameSettingsWindow::SlotUserHaveChangedMaximumNumberOfPlayers);
    QObject::connect(ui->spBox_TimeForOpponentsDecision, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &GameSettingsWindow::SlotUserHaveChangedTimeForOpponentsDecision);
    QObject::connect(ui->spBox_TimeToThink, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &GameSettingsWindow::SlotUserHaveChangedTimeToThink);
    QObject::connect(ui->chkBox_HasAddonWildAxe, &QCheckBox::clicked, this, &GameSettingsWindow::SlotUserHaveChangedHasAddonWildAxe);
    QObject::connect(ui->chckBox_HasAddonClericalErrors, &QCheckBox::clicked, this, &GameSettingsWindow::SlotUserHaveChangedHasAddonClericalErrors);
    QObject::connect(ui->lineEdit_UserName, &QLineEdit::textChanged, this, &GameSettingsWindow::SlotUserHaveChangedClientName);
    QObject::connect(ui->verticalScrollBar, &QScrollBar::sliderMoved, this, &GameSettingsWindow::SlotUserHaveChangedRulesType);
    QObject::connect(ui->buttonBox->button(QDialogButtonBox::StandardButton::Ok), &QPushButton::clicked, this, &GameSettingsWindow::SlotUserApplyedChangedSettings);
    QObject::connect(ui->buttonBox->button(QDialogButtonBox::StandardButton::Cancel), &QPushButton::clicked, this, &GameSettingsWindow::SlotUserRejectedChangedSettings);
    QObject::connect(ui->chckBox_AllowSettingsChanges, &QCheckBox::clicked, this, &GameSettingsWindow::SlotUserHaveChangedSettingsChangesAllowance);

}

void GameSettingsWindow::SetupInitialAllowedFeatures()
{
    ui->chkBox_HasAddonWildAxe->setCheckState(Qt::CheckState::Checked);
    ui->chckBox_HasAddonClericalErrors->setCheckState(Qt::CheckState::Checked);
    ui->chkBox_HasAddonWildAxe->setEnabled(false);
    ui->chckBox_HasAddonClericalErrors->setEnabled(false);
    ui->chckBox_AllowSettingsChanges->setCheckState(Qt::CheckState::Checked);

    ui->verticalScrollBar->setEnabled(false);

    ui->spBox_DiplomacyTime->setMaximum(300);
    ui->spBox_MaximumNumberOfPlayers->setMaximum(6);
    ui->spBox_TimeForOpponentsDecision->setMaximum(300);
    ui->spBox_TimeToThink->setMaximum(300);
    ui->spBox_TotalTimeToMove->setMaximum(420);

    ui->spBox_DiplomacyTime->setMinimum(10);
    ui->spBox_MaximumNumberOfPlayers->setMinimum(3);
    ui->spBox_TimeForOpponentsDecision->setMinimum(10);
    ui->spBox_TimeToThink->setMinimum(30);
    ui->spBox_TotalTimeToMove->setMinimum(20);

    ui->spBox_DiplomacyTime->setValue(_gameSettings.diplomacyTime());
    ui->spBox_MaximumNumberOfPlayers->setValue(_gameSettings.maximumNumberOfPlayers());
    ui->spBox_TimeForOpponentsDecision->setValue(_gameSettings.timeForOpponentsDecision());
    ui->spBox_TimeToThink->setValue(_gameSettings.timeToThink());
    ui->spBox_TotalTimeToMove->setValue(_gameSettings.totalTimeToMove());
    ui->lineEdit_UserName->setText(_gameSettings.clientName());

    ui->lbl_DiplomacyTime->setText(_DiplomacyTimeBaseText + QString::number(_gameSettings.diplomacyTime()) + " секунд.");
    ui->lbl_TimeForOpponentsDecision->setText(_TimeForOpponentsDecisionBaseText + QString::number(_gameSettings.timeForOpponentsDecision()) + " секунд.");
    ui->lbl_TimeToThink->setText(_TimeToThinkBaseText + QString::number(_gameSettings.timeToThink()) + " секунд.");
    switch (_gameSettings.maximumNumberOfPlayers())
    {
    case 3:
    case 4:
        ui->lbl_MaximumNumberOfPLayers->setText(_MaximumNumberOfPLayersBaseText + QString::number(_gameSettings.maximumNumberOfPlayers()) + " игрока.");
        break;
    default:
        ui->lbl_MaximumNumberOfPLayers->setText(_MaximumNumberOfPLayersBaseText + QString::number(_gameSettings.maximumNumberOfPlayers()) + " игроков.");
        break;
    }
    ui->lbl_RulesType->setText(_RulesTypeBaseText + (_gameSettings.rulesType() == RulesType::Automatic ? "Автоматические." : "Ручные!"));
    ui->lbl_TotalTimeToMove->setText(_TotalTimeToMoveBaseText +QString::number(_gameSettings.totalTimeToMove()) + " секунд.");
    ui->lbl_UserName->setText(_UserNameBaseText + _gameSettings.clientName());
    ui->lbl_HasAddonWildAxe->setText(_HasAddonWildAxeBaseText + (_gameSettings.hasAddonWildAxe() ? "используется." : "отключен."));
    ui->lbl_HasAddonClericalErrors->setText(_HasAddonClericalErrorsBaseText + (_gameSettings.hasAddonClericalErrors() ? "используется." : "отключен."));
    ui->lbl_AllowSettingsChanges->setText(_SettingsChangesBaseText + (_gameSettings.settingsCorrectionAllowed() ? "разрешено" : "запрещено"));
}

void GameSettingsWindow::SlotUserHaveChangedMaximumNumberOfPlayers(unsigned int val)
{
    _gameSettings.setMaximumNumberOfPlayers(val);
    switch (val)
    {
    case 3:
    case 4:
        ui->lbl_MaximumNumberOfPLayers->setText(_MaximumNumberOfPLayersBaseText + QString::number(val) + " игрока");
        break;
    default:
        ui->lbl_MaximumNumberOfPLayers->setText(_MaximumNumberOfPLayersBaseText + QString::number(val) + " игроков");
        break;
    }
    //emit SignalUserHaveChangedSettings(_gameSettings);
}

void GameSettingsWindow::SlotUserHaveChangedTotalTimeToMove(int val)
{
    _gameSettings.setTotalTimeToMove(val);
    ui->lbl_TotalTimeToMove->setText(_TotalTimeToMoveBaseText +QString::number(val) + " секунд.");
    //emit SignalUserHaveChangedSettings(_gameSettings);
}

void GameSettingsWindow::SlotUserHaveChangedTimeToThink(unsigned int val)
{
    _gameSettings.setTimeToThink(val);
    ui->lbl_TimeToThink->setText(_TimeToThinkBaseText + QString::number(val) + " секунд.");
    //emit SignalUserHaveChangedSettings(_gameSettings);
}

void GameSettingsWindow::SlotUserHaveChangedTimeForOpponentsDecision(unsigned int val)
{
    _gameSettings.setTimeForOpponentsDecision(val);
     ui->lbl_TimeForOpponentsDecision->setText(_TimeForOpponentsDecisionBaseText + QString::number(val) + " секунд.");
    //emit SignalUserHaveChangedSettings(_gameSettings);
}

void GameSettingsWindow::SlotUserHaveChangedDiplomacyTime(unsigned int val)
{
    _gameSettings.setDiplomacyTime(val);
    ui->lbl_DiplomacyTime->setText(_DiplomacyTimeBaseText + QString::number(val) + " секунд.");
    //emit SignalUserHaveChangedSettings(_gameSettings);
}

void GameSettingsWindow::SlotUserHaveChangedHasAddonClericalErrors(bool has)
{
    _gameSettings.setHasAddonClericalErrors(has);
    ui->lbl_HasAddonClericalErrors->setText(_HasAddonClericalErrorsBaseText + (has ? "используется." : "отключено."));
    //emit SignalUserHaveChangedSettings(_gameSettings);
}

void GameSettingsWindow::SlotUserHaveChangedHasAddonWildAxe(bool has)
{
    _gameSettings.setHasAddonWildAxe(has);
    ui->lbl_HasAddonWildAxe->setText(_HasAddonWildAxeBaseText + (has ? "используется." : "отключено."));
    //emit SignalUserHaveChangedSettings(_gameSettings);
}

void GameSettingsWindow::SlotUserHaveChangedClientName(const QString & clientName)
{
    _gameSettings.setClientName(clientName);
    ui->lbl_UserName->setText(_UserNameBaseText + clientName);
    //emit SignalUserHaveChangedSettings(_gameSettings);
}

void GameSettingsWindow::SlotUserHaveChangedRulesType(int automatic)
{
    _gameSettings.setRulesType((automatic ? RulesType::Automatic : RulesType::Manual));
    //NAY-001: MARK_EXPECTED_ERROR
    //Scroll may later provide any digit, but here will be only true/false selector!
    ui->lbl_RulesType->setText(_RulesTypeBaseText + (automatic ? "Автоматические." : "Ручные!"));
    //emit SignalUserHaveChangedSettings(_gameSettings);
}

void GameSettingsWindow::SlotUserHaveChangedSettingsChangesAllowance(bool allowed)
{
    _gameSettings.setSettingsCorrectionAllowed(allowed);
    ui->lbl_AllowSettingsChanges->setText(_SettingsChangesBaseText + (allowed ? "разрешено." : "запрещено"));
    //emit SignalUserHaveChangedSettings(_gameSettings);
}

void GameSettingsWindow::SlotUserApplyedChangedSettings(bool)
{
    emit SignalUserHaveChangedSettings(_gameSettings);
    close();
}

void GameSettingsWindow::SlotUserRejectedChangedSettings(bool)
{
    close();
}
