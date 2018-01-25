#ifndef HANDSECONDARYPLAYER_H
#define HANDSECONDARYPLAYER_H

#include <QWidget>

namespace Ui {
class HandSecondaryPlayer;
}

class HandSecondaryPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit HandSecondaryPlayer(QWidget *parent = 0);
    ~HandSecondaryPlayer();

private:
    Ui::HandSecondaryPlayer *ui;
};

#endif // HANDSECONDARYPLAYER_H
