#ifndef HANDSECONDARYPLAYER_H
#define HANDSECONDARYPLAYER_H

#include <QWidget>
#include <QDesktopWidget>
#include <QRect>
#include <QDebug>

#define DEBUG_HANDSECONDARY_PLAYER_WIDGET

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

private:

    //setup the koefficients;
    const float _race_class_btn_size_geometric_width_to_height_ratio = 2.71f;
    const float _race_class_btn_size_width = 0.035f;
    const float _race_class_btn_size_height = _race_class_btn_size_geometric_width_to_height_ratio*_race_class_btn_size_width;

private slots:

    void _slotTestHandButtons();

public slots:

    void _slot_updateCardsOnHandsTreasures(unsigned int);
    void _slot_updateCardsOnHandsDoors(unsigned int);

};

#endif // HANDSECONDARYPLAYER_H
