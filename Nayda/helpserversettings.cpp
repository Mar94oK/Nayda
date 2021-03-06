#include "helpserversettings.h"
#include "ui_helpserversettings.h"
#include <QFile>
#include <QTextStream>
#include <QTextDocument>

HelpServerSettings::HelpServerSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpServerSettings)
{
    ui->setupUi(this);
    setUpSettingsFilePath(":/HelpDocs/HelpServerSettings.html");
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

    QFile file(_filePath);
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    QString content = stream.readAll();
    file.close();
    ui->textBrowser->setHtml(content);
}
