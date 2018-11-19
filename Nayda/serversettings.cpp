#include "serversettings.h"
#include "ui_serversettings.h"
#include <QtNetwork>
#include <QDebug>


ServerSettings::ServerSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerSettings)
{
    ui->setupUi(this);
    
    QObject::connect(ui->btn_Help, &QPushButton::clicked, this, &ServerSettings::showHelp);
    QObject::connect(ui->btn_Save, &QPushButton::clicked, this, &ServerSettings::slotUserHasSavedServerSettings);

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

void ServerSettings::slotUserHasSavedServerSettings()
{
    if (!ui->cmbx_ServerName->currentText().isEmpty() && !ui->lineEdit_ServerName->text().isEmpty())
    {
        emit sig_userHaveChangedServerSettings(serverSettings(ui->cmbx_ServerName->currentText(), ui->lineEdit_ServerName->text()));
        qDebug() << "Server name: " << ui->cmbx_ServerName->currentText() << "Port: " << ui->lineEdit_ServerName->text();
        close();
        deleteLater();
    }
    else
    {
        qDebug() << "Please, set correct server settings!";
        ui->lbl_MessageForUser->setText("Пожалуйста, установите корректные настройки, прежде, чем сохранять.");
    }
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
