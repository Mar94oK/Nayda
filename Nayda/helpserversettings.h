#ifndef HELPSERVERSETTINGS_H
#define HELPSERVERSETTINGS_H

#include <QDialog>

namespace Ui {
class HelpServerSettings;
}

class HelpServerSettings : public QDialog
{
    Q_OBJECT

private:
    
    QString _filePath;

public:
    explicit HelpServerSettings(QWidget *parent = 0);
    ~HelpServerSettings();
    
    void setUpSettingsFilePath(QString path)
    {
        _filePath = path;
    }

private:
    Ui::HelpServerSettings *ui;
    void setUpSettingsTextBrowser();
    
    
};

#endif // HELPSERVERSETTINGS_H
