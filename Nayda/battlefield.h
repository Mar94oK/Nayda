#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QDesktopWidget>
#include <Application/card.h>
#include <QPushButton>
#include <QTimer>
#include <QLabel>
#include <QSpacerItem>
#include "Application/card.h"
#include "gamesettings.h"
#include "Application/The_Game/The_Game.h"
#include "playersordernotification.h"
#include "smartqtlogger.h"

namespace Ui {
class battleField;
}

class battleField : public QWidget
{
    Q_OBJECT

private:

    Logger logger;

public:
    explicit battleField(QWidget *parent = 0);
    ~battleField();


    void cardsRepresenter();

    void setMonsersDeck(const std::map<int, gameCardDoorMonster> *monsersDeck);
    void setAmplifiersDeck(const std::map<int, gameCardDoorAmplifier> *amplifiersDeck);
    void setCursesDeck(const std::map<int, gameCardDoorCurse> *cursesDeck);
    void setProfessionsDeck(const std::map<int, gameCardDoorProfession> *professionsDeck);
    void setRacesDeck(const std::map<int, gameCardDoorRace> *racesDeck);
    void setSpecialMechanicsDeck(const std::map<int, gameCardDoorSpecialMechanic> *specialMechanicsDeck);
    void setArmorDeck(const std::map<int, gameCardTreasureArmor> *armorDeck);
    void setArmorAmplifiersDeck(const std::map<int, gameCardTreasureArmorAmplifier> *armorAmplifiersDeck);
    void setBattleAmplifiersDeck(const std::map<int, gameCardTreasureBattleAmplifier> *battleAmplifiersDeck);
    void setLevelUpDeck(const std::map<int, gameCardTreasureLevelUp> *levelUpDeck);
    void setSpecialMechanicsTreasureDeck(const std::map<int, gameCardTreasureSpecialMechanic> *specialMechanicsTreasureDeck);
    void setThingsAmplifiersDeck(const std::map<int, gameCardTreasureThingsAmplifiers> *thingsAmplifiersDeck);
    void setWeaponsDeck(const std::map<int, gameCardTreasureWeapon> *weaponsDeck);

private:
    Ui::battleField *ui;

    //const std::map<int, gameCardDoorMonster> &_monsersDeck;
    const std::map<int, gameCardDoorMonster> *_monstersDeck;
    const std::map<int, gameCardDoorAmplifier> *_amplifiersDeck;
    const std::map<int, gameCardDoorCurse> *_cursesDeck;
    const std::map<int, gameCardDoorProfession> *_professionsDeck;
    const std::map<int, gameCardDoorRace> *_racesDeck;
    const std::map<int, gameCardDoorSpecialMechanic> *_specialMechanicsDeck;

    const std::map<int, gameCardTreasureArmor> *_armorDeck;
    const std::map<int, gameCardTreasureArmorAmplifier> *_armorAmplifiersDeck;
    const std::map<int, gameCardTreasureBattleAmplifier> *_battleAmplifiersDeck;
    const std::map<int, gameCardTreasureLevelUp> *_levelUpDeck;
    const std::map<int, gameCardTreasureSpecialMechanic> *_specialMechanicsTreasureDeck;
    const std::map<int, gameCardTreasureThingsAmplifiers> *_thingsAmplifiersDeck;
    const std::map<int, gameCardTreasureWeapon> *_weaponsDeck;

    std::map<int, gameCardDoorMonster> :: const_iterator  _monstersIterator;
    std::map<int, gameCardDoorAmplifier> :: const_iterator _amplifiersIterator;
    std::map<int, gameCardDoorCurse> :: const_iterator _cursesIterator;
    std::map<int, gameCardDoorProfession> :: const_iterator _professionsIterator;
    std::map<int, gameCardDoorRace> :: const_iterator _racesIterator;
    std::map<int, gameCardDoorSpecialMechanic> :: const_iterator _specialMechanicsIterator;

    std::map<int, gameCardTreasureArmor> :: const_iterator _armorIterator;
    std::map<int, gameCardTreasureArmorAmplifier> :: const_iterator _armorAmplifiersIterator;
    std::map<int, gameCardTreasureBattleAmplifier> :: const_iterator _battleAmplifiersIterator;
    std::map<int, gameCardTreasureLevelUp> :: const_iterator _levelUpIterator;
    std::map<int, gameCardTreasureSpecialMechanic> :: const_iterator _specialMechanicsTreasureIterator;
    std::map<int, gameCardTreasureThingsAmplifiers> :: const_iterator _thingsAmplifiersIterator;
    std::map<int, gameCardTreasureWeapon> :: const_iterator _weaponsIterator;

    QTimer *_showCardsTimer;
    QPushButton* _theBtnMainRepresenter;
    QPushButton* _theBtnRepresenter1;
    QPushButton* _theBtnRepresenter2;
    QPushButton* _theBtnRepresenter3;
    QPushButton* _theBtnRepresenter4;
    QPushButton* _theBtnRepresenter5;

    const float _race_class_btn_size_geometric_width_to_height_ratio = 2.71f;
    const float _race_class_btn_size_width = 0.0415f;
    const float _race_class_btn_size_height = _race_class_btn_size_geometric_width_to_height_ratio*_race_class_btn_size_width;

    bool _continueToRepresentCards = false;
    unsigned int _currCardsArrayRepresentationStep = 0;
    int _timerCount = 100;

public slots:

   void continueCardRepresentation();
   void startCardsRepresentation();

private:

   void SetBackgroundPicture();

//Setting-up Start-Up Procedure.
private:

   void SetWidgetsToStartUpPhase();

   QLabel* _startUpTimerTextLabel;
   QLabel* _timeLeftBeforeStartUpLabel;
   QString _startUpTimerText = "До начала игры осталось: ";
   QTimer* _startUpTimer;
   const uint32_t _startUpTimeSeconds = 1;
   const uint32_t _startUpShowOrderTime = 1;
   uint32_t _startUpTimerTicksCounter = 0;

   QSpacerItem * _spacerBottom;
   QSpacerItem * _spacerForScene2;
   QSpacerItem * _spacerForScene2_2;

   QString _phaseNameInitialPhaseText = "Ожидание хода игрока ";

   PlayersOrderNotification* _orderNotification;



   void SetFontAndAlignment(QLabel* lbl);

   void ShowInitialAnimationScene_1();
   void HideInitialAnimationScene_1();
   void ShowInitialAnimationScene_2();
   void HideInitialAnimationScene_2();

public:

   void InitializeStartUpProcedureVisualization();

   std::vector<QString> playersOrder() const;
   void setPlayersOrder(const std::vector<QString> &playersOrder);

private slots:

   void SlotStartUpTimerHandler();
   void SlotStartUpAnimationCompleted();

signals:

   void SignalStartUpAnimationCompleted();

private:

   void SetUpSignalsSlotsConnections();

private:

   QPainter* _painter;
   bool _painterInitialized = false;


private:

   QString _diplomacyTimerPictureAddress = "";
   QString _timeToMoveTimerPictureAddress = "";
   QString _timeForOpponentsToDecideTimerPictureAddress = "";
   QString _timeToThinkTimerPictureAddress = "";

   void SetUpPictureAddresses();
   void SetUpInitialTimersPictures();
   void SetUpButtonPicture(QPushButton* const btn, const QString& picturePath, double widthCoeff, double heightWidthRelatio);

   //These sizes should be selected with respect to the TimerText Height.
   const double _buttonsWidthCoefficient = 0.1;
   const double _buttonsHeightWidthRelatio = 1.24633;

private:

   GameSettings _settings;

   std::vector<QString> _playersOrder;

private:

   std::vector<QPushButton* > _forCards;
   std::vector<QPushButton* > _againstCards;

   void AddCardToForCards(SimpleCard card);
   void AddCardToAgainstCards(SimpleCard card);
   void AddCardToSpecialMechanics(SimpleCard card);

   void InitializeBattle();

private slots:

   void SlotChangeMoveTimerTime(uint32_t time);
   void SlotChangePhaseTimerTime(uint32_t time);
   void SlotGamePhaseHasBeenChanged(GamePhase phase);

public slots:

    void ApplyNewSettings(GameSettings settings)
    { _settings.applyNewSettings(settings); }

public:

    void SetTimeLeftMoveTimer(uint32_t secondsLeft);
    void SetTimeLeftPhaseTimer(uint32_t secondsLeft);


private:

    QString _initialMoveTimerText = "До конца хода осталось: ";
    QString _initialPhaseTimerText = "До конца фазы осталось: ";

    QString _initialMoveTimeText = "1";
    QString _initialPhaseTimeText = "1";

    void SetUpTimersLabels();
    void SetFontAndAlignment(QLabel* lbl, uint32_t size);

};



#endif // BATTLEFIELD_H
