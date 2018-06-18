#include "serversettings.h"
#include "ui_serversettings.h"

ServerSettings::ServerSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerSettings)
{
    ui->setupUi(this);
    
    //QObject::connect(ui->btbx_AcceptReject->)
}

ServerSettings::~ServerSettings()
{
    delete ui;
}

void ServerSettings::showHelp(void)
{
    helpPage = new HelpServerSettings(this);
    helpPage->setModal(true);
    helpPage->show();
}
