#ifndef HELPSERVERSETTINGS_H
#define HELPSERVERSETTINGS_H

#include <QDialog>

namespace Ui {
class HelpServerSettings;
}

class HelpServerSettings : public QDialog
{
    Q_OBJECT

public:
    explicit HelpServerSettings(QWidget *parent = 0);
    ~HelpServerSettings();

private:
    Ui::HelpServerSettings *ui;
    void setUpSettingsTextBrowser();
};

#endif // HELPSERVERSETTINGS_H
