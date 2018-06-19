#ifndef SERVERSETTINGS_H
#define SERVERSETTINGS_H

#include <QDialog>
#include <helpserversettings.h>

namespace Ui {
class ServerSettings;
}

class ServerSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ServerSettings(QWidget *parent = 0);
    ~ServerSettings();
    
public slots:

    void showHelp(void);

private:
    
    Ui::ServerSettings *ui;
    HelpServerSettings* helpPage = nullptr;

    void setServerNameComboBox();
};

#endif // SERVERSETTINGS_H
