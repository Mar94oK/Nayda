#include "gamesettingswidget.h"
#include "ui_gamesettingswidget.h"

GameSettingsWidget::GameSettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameSettingsWidget)
{
    ui->setupUi(this);
}

GameSettingsWidget::~GameSettingsWidget()
{
    delete ui;
}
