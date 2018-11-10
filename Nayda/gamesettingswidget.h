#ifndef GAMESETTINGSWIDGET_H
#define GAMESETTINGSWIDGET_H

#include <QWidget>

namespace Ui {
class GameSettingsWidget;
}

class GameSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameSettingsWidget(QWidget *parent = 0);
    ~GameSettingsWidget();

private:
    Ui::GameSettingsWidget *ui;
};

#endif // GAMESETTINGSWIDGET_H
