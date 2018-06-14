#include "helpserversettings.h"
#include "ui_helpserversettings.h"

HelpServerSettings::HelpServerSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpServerSettings)
{
    ui->setupUi(this);
    setUpSettingsTextBrowser();
}

HelpServerSettings::~HelpServerSettings()
{
    delete ui;
}

void HelpServerSettings::setUpSettingsTextBrowser()
{
    ui->textBrowser->openExternalLinks();
    ui->textBrowser->acceptRichText();
    ui->textBrowser->openExternalLinks();
    ui->textBrowser->setReadOnly(true);
}
