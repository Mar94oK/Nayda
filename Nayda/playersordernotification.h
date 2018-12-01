#ifndef PLAYERSORDERNOTIFICATION_H
#define PLAYERSORDERNOTIFICATION_H

#include <QWidget>
#include <QString>
#include <QLabel>

namespace Ui {
class PlayersOrderNotification;
}

class PlayersOrderNotification : public QWidget
{
    Q_OBJECT

public:
    explicit PlayersOrderNotification(QWidget *parent = nullptr);
    ~PlayersOrderNotification();

private:
    Ui::PlayersOrderNotification *ui;

private:

    std::vector<QString> _playersOrder;
    std::vector<QLabel* > _orderLabels;

public:

    void AddPlayer(const QString& playerName);

private:

    void SetUpFonts(QLabel* lbl);

};

#endif // PLAYERSORDERNOTIFICATION_H
