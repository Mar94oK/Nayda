#include "serversettings.h"
#include "ui_serversettings.h"
#include <QtNetwork>


ServerSettings::ServerSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerSettings)
{
    ui->setupUi(this);
    
    QObject::connect(ui->btn_Help, &QPushButton::clicked, this, &ServerSettings::showHelp);

    setServerNameComboBox();
    ui->lineEdit_ServerName->setValidator(new QIntValidator(1, 65535, this));

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

void ServerSettings::setServerNameComboBox()
{
    ui->cmbx_ServerName->setEditable(true);
    QString name = QHostInfo::localHostName();
    if (!name.isEmpty())
    {
        ui->cmbx_ServerName->addItem(name);
        QString domain = QHostInfo::localDomainName();
        if (!domain.isEmpty())
            ui->cmbx_ServerName->addItem(name + QChar('.') + domain);
    }
    if (name != QLatin1String("localhost"))
        ui->cmbx_ServerName->addItem(QString("localhost"));
    // find out IP addresses of this machine
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // add non-localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (!ipAddressesList.at(i).isLoopback())
            ui->cmbx_ServerName->addItem(ipAddressesList.at(i).toString());
    }
    // add localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i).isLoopback())
            ui->cmbx_ServerName->addItem(ipAddressesList.at(i).toString());
    }
}
