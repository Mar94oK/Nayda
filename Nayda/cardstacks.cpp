#include "cardstacks.h"
#include "ui_cardstacks.h"
#include "munchkinglobaldefines.h"

CardStacks::CardStacks(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CardStacks)
{
    ui->setupUi(this);

    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Height = HW_Screen_Size.height();

    //set-up the initial Stacks
    //_race_class_btn_size_geometric_width_to_height_ratio*_race_class_btn_size_width

    QPixmap doorsStackImage(_doorsStackLevelsPictures[0]);
    QPalette plte_doorStack;
    plte_doorStack.setBrush(ui->btn_DoorsStack->backgroundRole(),
    QBrush(doorsStackImage.scaled((_race_class_btn_size_width + increasingStacksSizeDeltaWidth )*HW_Screen_Size_Width,
                                  (_race_class_btn_size_height + increasingStacksSizeDeltaHeight )*HW_Screen_Size_Height,
                                  Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    ui->btn_DoorsStack->setMinimumHeight((_race_class_btn_size_height + increasingStacksSizeDeltaHeight )*HW_Screen_Size_Height);
    ui->btn_DoorsStack->setMaximumHeight((_race_class_btn_size_height + increasingStacksSizeDeltaHeight)*HW_Screen_Size_Height);
    ui->btn_DoorsStack->setMinimumWidth((_race_class_btn_size_width + increasingStacksSizeDeltaWidth)*HW_Screen_Size_Width);
    ui->btn_DoorsStack->setMaximumWidth((_race_class_btn_size_width + increasingStacksSizeDeltaWidth)*HW_Screen_Size_Width);

    ui->btn_DoorsStack->setFlat(true);
    ui->btn_DoorsStack->setAutoFillBackground(true);
    ui->btn_DoorsStack->setPalette(plte_doorStack);
    ui->btn_DoorsStack->setText("");
    //ui->btn_DoorsStack->installEventFilter(this);

    if (_showTheNumberOfCardsLeft) {
        ui->lbl_DoorsStack->setText(QString::number(_doorsLeft));
    }

    QPixmap treasuresStackImage(_treasuresStackLevelPictures[0]);
    QPalette plte_treasureStack;
    plte_treasureStack.setBrush(ui->btn_TreasuresStack->backgroundRole(),
    QBrush(treasuresStackImage.scaled((_race_class_btn_size_width + increasingStacksSizeDeltaWidth )*HW_Screen_Size_Width,
                                      (_race_class_btn_size_height + increasingStacksSizeDeltaHeight )*HW_Screen_Size_Height,
                                      Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    ui->btn_TreasuresStack->setMinimumHeight((_race_class_btn_size_height + increasingStacksSizeDeltaHeight )*HW_Screen_Size_Height);
    ui->btn_TreasuresStack->setMaximumHeight((_race_class_btn_size_height + increasingStacksSizeDeltaHeight)*HW_Screen_Size_Height);
    ui->btn_TreasuresStack->setMinimumWidth((_race_class_btn_size_width + increasingStacksSizeDeltaWidth)*HW_Screen_Size_Width);
    ui->btn_TreasuresStack->setMaximumWidth((_race_class_btn_size_width + increasingStacksSizeDeltaWidth)*HW_Screen_Size_Width);

    ui->btn_TreasuresStack->setFlat(true);
    ui->btn_TreasuresStack->setAutoFillBackground(true);
    ui->btn_TreasuresStack->setPalette(plte_treasureStack);
    ui->btn_TreasuresStack->setText("");
    //ui->btn_DoorsStack->installEventFilter(this);

    if (_showTheNumberOfCardsLeft)
        ui->lbl_TreasuresStack->setText(QString::number(_treasuresLeft));

    //set Folds

    ui->btn_DoorsFold->setMinimumHeight((_race_class_btn_size_height + increasingStacksSizeDeltaHeight )*HW_Screen_Size_Height);
    ui->btn_DoorsFold->setMaximumHeight((_race_class_btn_size_height + increasingStacksSizeDeltaHeight)*HW_Screen_Size_Height);
    ui->btn_DoorsFold->setMinimumWidth((_race_class_btn_size_width + increasingStacksSizeDeltaWidth)*HW_Screen_Size_Width);
    ui->btn_DoorsFold->setMaximumWidth((_race_class_btn_size_width + increasingStacksSizeDeltaWidth)*HW_Screen_Size_Width);

    ui->btn_TreasuresFold->setMinimumHeight((_race_class_btn_size_height + increasingStacksSizeDeltaHeight )*HW_Screen_Size_Height);
    ui->btn_TreasuresFold->setMaximumHeight((_race_class_btn_size_height + increasingStacksSizeDeltaHeight)*HW_Screen_Size_Height);
    ui->btn_TreasuresFold->setMinimumWidth((_race_class_btn_size_width + increasingStacksSizeDeltaWidth)*HW_Screen_Size_Width);
    ui->btn_TreasuresFold->setMaximumWidth((_race_class_btn_size_width + increasingStacksSizeDeltaWidth)*HW_Screen_Size_Width);

#ifndef USE_RESOURCES
    QPixmap doorsFoldImage("Pictures/doorsAreOpened.jpg");
#else
    QPixmap doorsFoldImage(":/Pictures/doorsAreOpened.jpg");
#endif

    QPalette plte_doorFold;
    plte_doorFold.setBrush(ui->btn_DoorsFold->backgroundRole(),
    QBrush(doorsFoldImage.scaled((_race_class_btn_size_width + increasingStacksSizeDeltaWidth )*HW_Screen_Size_Width,
                                  (_race_class_btn_size_height + increasingStacksSizeDeltaHeight )*HW_Screen_Size_Height,
                                  Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    ui->btn_DoorsFold->setFlat(true);
    ui->btn_DoorsFold->setAutoFillBackground(true);
    ui->btn_DoorsFold->setPalette(plte_doorFold);
    ui->btn_DoorsFold->setText("");

#ifndef USE_RESOURCES
    QPixmap treasureFoldImage("Pictures/TreasuresCard.png");
#else
    QPixmap treasureFoldImage(":/Pictures/TreasuresCard.png");
#endif

    QPalette plte_treasureFold;
    plte_treasureFold.setBrush(ui->btn_TreasuresFold->backgroundRole(),
    QBrush(treasureFoldImage.scaled((_race_class_btn_size_width + increasingStacksSizeDeltaWidth )*HW_Screen_Size_Width,
                                  (_race_class_btn_size_height + increasingStacksSizeDeltaHeight )*HW_Screen_Size_Height,
                                  Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    ui->btn_TreasuresFold->setFlat(true);
    ui->btn_TreasuresFold->setAutoFillBackground(true);
    ui->btn_TreasuresFold->setPalette(plte_treasureFold);
    ui->btn_TreasuresFold->setText("");

#ifdef DEBUG_CARDSTACKS_WIDGET
    _testTimer = new QTimer();
    _testTimer->setInterval(250);
    _testTimer->setSingleShot(false);

    connect(ui->btn_Test, &QPushButton::clicked, this, &CardStacks::startTheTest);
    connect(_testTimer, &QTimer::timeout, this, &CardStacks::testTheFoldProcess);
#endif
}

CardStacks::~CardStacks()
{
    delete ui;
}

void CardStacks::changeTheDoorsStackView(unsigned int cardsLeft)
{
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Height = HW_Screen_Size.height();

    unsigned int stage = 0;
    if (cardsLeft > 100) {
        stage = 0;
    }
    else if ((cardsLeft < 101) && (cardsLeft > 70) ) {
        stage = 1;
    }
    else if ((cardsLeft < 71) && (cardsLeft > 30) ) {
        stage = 2;
    }
    else if ((cardsLeft < 31) && (cardsLeft > 1) ) {
        stage = 3;
    }
    else if (cardsLeft == 1) {
        stage = 4;
    }
    else {
        stage = 5; //clear the stack!
    }

    QPixmap doorsStackImage(_doorsStackLevelsPictures[stage]);
    QPalette plte_doorStack;
    plte_doorStack.setBrush(ui->btn_DoorsStack->backgroundRole(),
    QBrush(doorsStackImage.scaled(_race_class_btn_size_width*HW_Screen_Size_Width,
                                    _race_class_btn_size_height*HW_Screen_Size_Height / 2,
                                    Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    ui->btn_DoorsStack->setFlat(true);
    ui->btn_DoorsStack->setAutoFillBackground(true);
    ui->btn_DoorsStack->setPalette(plte_doorStack);
    ui->btn_DoorsStack->setText("");
    //ui->btn_DoorsStack->installEventFilter(this);

    if (_showTheNumberOfCardsLeft)
    {
        ui->lbl_DoorsStack->setText(QString::number(cardsLeft));
    }
}

void CardStacks::changeTheTreasureStackView(unsigned int cardsLeft)
{
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Height = HW_Screen_Size.height();

    unsigned int stage = 0;
    if (cardsLeft > 100) {
        stage = 0;
    }
    else if ((cardsLeft < 101) && (cardsLeft > 70) ) {
        stage = 1;
    }
    else if ((cardsLeft < 71) && (cardsLeft > 30) ) {
        stage = 2;
    }
    else if ((cardsLeft < 31) && (cardsLeft > 1) ) {
        stage = 3;
    }
    else if (cardsLeft == 1) {
        stage = 4;
    }
    else {
        stage = 5; //clear the stack!
    }

    QPixmap treasuresStackImage(_treasuresStackLevelPictures[stage]);
    QPalette plte_treasuresStack;
    plte_treasuresStack.setBrush(ui->btn_TreasuresStack->backgroundRole(),
    QBrush(treasuresStackImage.scaled(_race_class_btn_size_width*HW_Screen_Size_Width,
                                    _race_class_btn_size_height*HW_Screen_Size_Height / 2,
                                    Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

    ui->btn_TreasuresStack->setFlat(true);
    ui->btn_TreasuresStack->setAutoFillBackground(true);
    ui->btn_TreasuresStack->setPalette(plte_treasuresStack);
    ui->btn_TreasuresStack->setText("");

    //Show the Number of Cards Left
    if (_showTheNumberOfCardsLeft) {
        ui->lbl_TreasuresStack->setText(QString::number(cardsLeft));
    }
}

void CardStacks::passTheCardToFoldStack(SimpleCard card)
{
    if (card.first) {
        _treasuresFold.push_back(card);
    }
    else {
        _doorsFold.push_back(card);
    }

    //and redraw the Picture!

    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Height = HW_Screen_Size.height();

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

    QString currentPictureAddress;
    bool isFound = false;
    if (!card.first) { //door

        _monstersIterator = _monstersDeck->find(static_cast <int> (card.second));
        if (_monstersIterator != _monstersDeck->end()) {
            currentPictureAddress = (*_monstersIterator).second.pictureAddress();
            isFound = true;
        }
        if (!isFound) {
            _amplifiersIterator = _amplifiersDeck->find(static_cast <int> (card.second));
            if (_amplifiersIterator != _amplifiersDeck->end()) {
                currentPictureAddress = (*_amplifiersIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _cursesIterator = _cursesDeck->find(static_cast <int> (card.second));
            if (_cursesIterator != _cursesDeck->end()) {
                currentPictureAddress = (*_cursesIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _professionsIterator = _professionsDeck->find(static_cast <int> (card.second));
            if (_professionsIterator != _professionsDeck->end()) {
                currentPictureAddress = (*_professionsIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _racesIterator = _racesDeck->find(static_cast <int> (card.second));
            if (_racesIterator != _racesDeck->end()) {
                currentPictureAddress = (*_racesIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _specialMechanicsIterator = _specialMechanicsDeck->find(static_cast <int> (card.second));
            if (_specialMechanicsIterator != _specialMechanicsDeck->end()) {
                currentPictureAddress = (*_specialMechanicsIterator).second.pictureAddress();
                isFound = true;
            }
        }
    }
    else { //treasure


        _armorIterator = _armorDeck->find(static_cast <int> (card.second));
        if (_armorIterator != _armorDeck->end()) {
            currentPictureAddress = (*_armorIterator).second.pictureAddress();
            isFound = true;
        }
        if (!isFound) {
            _armorAmplifiersIterator = _armorAmplifiersDeck->find(static_cast <int> (card.second));
            if (_armorAmplifiersIterator != _armorAmplifiersDeck->end()) {
                currentPictureAddress = (*_armorAmplifiersIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _battleAmplifiersIterator = _battleAmplifiersDeck->find(static_cast <int> (card.second));
            if (_battleAmplifiersIterator != _battleAmplifiersDeck->end()) {
                currentPictureAddress = (*_battleAmplifiersIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _levelUpIterator = _levelUpDeck->find(static_cast <int> (card.second));
            if (_levelUpIterator != _levelUpDeck->end()) {
                currentPictureAddress = (*_levelUpIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _specialMechanicsTreasureIterator = _specialMechanicsTreasureDeck->find(static_cast <int> (card.second));
            if (_specialMechanicsTreasureIterator != _specialMechanicsTreasureDeck->end()) {
                currentPictureAddress = (*_specialMechanicsTreasureIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _thingsAmplifiersIterator = _thingsAmplifiersDeck->find(static_cast <int> (card.second));
            if (_thingsAmplifiersIterator != _thingsAmplifiersDeck->end()) {
                currentPictureAddress = (*_thingsAmplifiersIterator).second.pictureAddress();
                isFound = true;
            }
        }
        if (!isFound) {
            _weaponsIterator = _weaponsDeck->find(static_cast <int> (card.second));
            if (_weaponsIterator != _weaponsDeck->end()) {
                currentPictureAddress = (*_weaponsIterator).second.pictureAddress();
                isFound = true;
            }
        }
    }

    if (!isFound) qDebug() << "Error during passing Cards to the Hands Shower! Check the number passed! " << card.second;

    if (!card.first) {

        QPixmap docksFoldImage(currentPictureAddress);
        QPalette plte_doorsFoldStack;
        plte_doorsFoldStack.setBrush(ui->btn_DoorsFold->backgroundRole(),
                                         QBrush(docksFoldImage.scaled((_race_class_btn_size_width + increasingStacksSizeDeltaWidth )*HW_Screen_Size_Width,
                                                                      (_race_class_btn_size_height + increasingStacksSizeDeltaHeight )*HW_Screen_Size_Height,
                                                                      Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

        ui->btn_DoorsFold->setFlat(true);
        ui->btn_DoorsFold->setAutoFillBackground(true);
        ui->btn_DoorsFold->setPalette(plte_doorsFoldStack);
        ui->btn_DoorsFold->setText("");
        //ui->btn_DoorsStack->installEventFilter(this);
        //set the Value
        ui->lbl_DoorsFold->setText(QString::number(_doorsFold.size()));
    }
    else {

        QPixmap treasuresFoldImage(currentPictureAddress);
        QPalette plte_treasuresFoldStack;
        plte_treasuresFoldStack.setBrush(ui->btn_TreasuresFold->backgroundRole(),
                                         QBrush(treasuresFoldImage.scaled((_race_class_btn_size_width + increasingStacksSizeDeltaWidth )*HW_Screen_Size_Width,
                                                                          (_race_class_btn_size_height + increasingStacksSizeDeltaHeight )*HW_Screen_Size_Height,
                                                                           Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

        ui->btn_TreasuresFold->setFlat(true);
        ui->btn_TreasuresFold->setAutoFillBackground(true);
        ui->btn_TreasuresFold->setPalette(plte_treasuresFoldStack);
        ui->btn_TreasuresFold->setText("");
        //ui->btn_DoorsStack->installEventFilter(this);
        //set the Value
        ui->lbl_TreasuresFold->setText(QString::number(_treasuresFold.size()));
    }
}

unsigned int CardStacks::treasuresLeft() const
{
    return _treasuresLeft;
}

void CardStacks::setTreasuresLeft(unsigned int treasuresLeft)
{
    _treasuresLeft = treasuresLeft;
}

unsigned int CardStacks::doorsLeft() const
{
    return _doorsLeft;
}

void CardStacks::setDoorsLeft(unsigned int doorsLeft)
{
    _doorsLeft = doorsLeft;
}

unsigned int CardStacks::totalDoors() const
{
    return _totalDoors;
}

void CardStacks::setTotalDoors(unsigned int totalDoors)
{
    _totalDoors = totalDoors;
}

unsigned int CardStacks::totalTreasures() const
{
    return _totalTreasures;
}

void CardStacks::setTotalTreasures(unsigned int totalTreasures)
{
    _totalTreasures = totalTreasures;
}

void CardStacks::updateTreasuresLeft(unsigned int treasuresLeft)
{
    _treasuresLeft = treasuresLeft;
    ui->lbl_TreasuresStack->setText(QString::number(treasuresLeft));
}

void CardStacks::updateDoorsLeft(unsigned int doorsLeft)
{
    _doorsLeft = doorsLeft;
    ui->lbl_DoorsStack->setText(QString::number(doorsLeft));
}

void CardStacks::testTheFoldProcess()
{
    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Height = HW_Screen_Size.height();

    SimpleCard currentCard;
    if (!_currCardsArrayRepresentationStep) {

        _monstersIterator = _monstersDeck->begin();
        _amplifiersIterator = _amplifiersDeck->begin();
        _cursesIterator = _cursesDeck->begin();
        _professionsIterator = _professionsDeck->begin();
        _racesIterator = _racesDeck->begin();
        _specialMechanicsIterator = _specialMechanicsDeck->begin();

        _armorIterator = _armorDeck->begin();
        _armorAmplifiersIterator = _armorAmplifiersDeck->begin();
        _battleAmplifiersIterator = _battleAmplifiersDeck->begin();
        _levelUpIterator = _levelUpDeck->begin();
        _specialMechanicsTreasureIterator = _specialMechanicsTreasureDeck->begin();
        _thingsAmplifiersIterator = _thingsAmplifiersDeck->begin();
        _weaponsIterator = _weaponsDeck->begin();
    }
    if (_currCardsArrayRepresentationStep < _monstersDeck->size()) {
        currentCard.first = false;
        currentCard.second = _monstersIterator->second.cardID();

        _monstersIterator++;
        _currCardsArrayRepresentationStep++;
    }
    else if (_currCardsArrayRepresentationStep < (_monstersDeck->size()
             + _amplifiersDeck->size())){
        currentCard.first = false;
        currentCard.second = _amplifiersIterator->second.cardID();
        _amplifiersIterator++;
        _currCardsArrayRepresentationStep++;
    }
    else if (_currCardsArrayRepresentationStep < (_monstersDeck->size()
             + _amplifiersDeck->size() + _cursesDeck->size())){
        currentCard.first = false;
        currentCard.second = _cursesIterator->second.cardID();
        _cursesIterator++;
        _currCardsArrayRepresentationStep++;
    }
    else if (_currCardsArrayRepresentationStep < (_monstersDeck->size()
             + _amplifiersDeck->size() + _cursesDeck->size() + _professionsDeck->size())){
        currentCard.first = false;
        currentCard.second = _professionsIterator->second.cardID();
        _professionsIterator++;
        _currCardsArrayRepresentationStep++;
    }
    else if (_currCardsArrayRepresentationStep < (_monstersDeck->size()
             + _amplifiersDeck->size() + _cursesDeck->size() + _professionsDeck->size() +
                                                  _racesDeck->size())){
        currentCard.first = false;
        currentCard.second = _racesIterator->second.cardID();
        _racesIterator++;
        _currCardsArrayRepresentationStep++;
    }
    else if (_currCardsArrayRepresentationStep < (_monstersDeck->size()
             + _amplifiersDeck->size() + _cursesDeck->size() + _professionsDeck->size() +
                                                  _racesDeck->size() + _specialMechanicsDeck->size())){
        currentCard.first = false;
        currentCard.second = _specialMechanicsIterator->second.cardID();
        _specialMechanicsIterator++;
        _currCardsArrayRepresentationStep++;
    }

    else if (_currCardsArrayRepresentationStep < (_monstersDeck->size()
                                                   + _amplifiersDeck->size() + _cursesDeck->size()
                                                   + _professionsDeck->size() + _racesDeck->size()
                                                   + _specialMechanicsDeck->size()
                                                   + _armorDeck->size())){
        currentCard.first = true;
        currentCard.second = _armorIterator->second.cardID();
        _armorIterator++;
        _currCardsArrayRepresentationStep++;
    }
    else if (_currCardsArrayRepresentationStep < (_monstersDeck->size()
                                                   + _amplifiersDeck->size() + _cursesDeck->size()
                                                   + _professionsDeck->size() + _racesDeck->size()
                                                   + _specialMechanicsDeck->size()
                                                   + _armorDeck->size() + _armorAmplifiersDeck->size())){
        currentCard.first = true;
        currentCard.second = _armorAmplifiersIterator->second.cardID();
        _armorAmplifiersIterator++;
        _currCardsArrayRepresentationStep++;
    }
    else if (_currCardsArrayRepresentationStep < (_monstersDeck->size()
                                                   + _amplifiersDeck->size() + _cursesDeck->size()
                                                   + _professionsDeck->size() + _racesDeck->size()
                                                   + _specialMechanicsDeck->size()
                                                   + _armorDeck->size() + _armorAmplifiersDeck->size()
                                                   + _battleAmplifiersDeck->size())){
        currentCard.first = true;
        currentCard.second = _battleAmplifiersIterator->second.cardID();
        _battleAmplifiersIterator++;
        _currCardsArrayRepresentationStep++;
    }
    else if (_currCardsArrayRepresentationStep < (_monstersDeck->size()
                                                   + _amplifiersDeck->size() + _cursesDeck->size()
                                                   + _professionsDeck->size() + _racesDeck->size()
                                                   + _specialMechanicsDeck->size()
                                                   + _armorDeck->size() + _armorAmplifiersDeck->size()
                                                   + _battleAmplifiersDeck->size() + _levelUpDeck->size())){
        currentCard.first = true;
        currentCard.second = _levelUpIterator->second.cardID();
        _levelUpIterator++;
        _currCardsArrayRepresentationStep++;
    }
    else if (_currCardsArrayRepresentationStep < (_monstersDeck->size()
                                                   + _amplifiersDeck->size() + _cursesDeck->size()
                                                   + _professionsDeck->size() + _racesDeck->size()
                                                   + _specialMechanicsDeck->size()
                                                   + _armorDeck->size() + _armorAmplifiersDeck->size()
                                                   + _battleAmplifiersDeck->size() + _levelUpDeck->size()
                                                   + _specialMechanicsTreasureDeck->size())){
        currentCard.first = true;
        currentCard.second = _specialMechanicsTreasureIterator->second.cardID();
        _specialMechanicsTreasureIterator++;
        _currCardsArrayRepresentationStep++;
    }
    else if (_currCardsArrayRepresentationStep < (_monstersDeck->size()
                                                   + _amplifiersDeck->size() + _cursesDeck->size()
                                                   + _professionsDeck->size() + _racesDeck->size()
                                                   + _specialMechanicsDeck->size()
                                                   + _armorDeck->size() + _armorAmplifiersDeck->size()
                                                   + _battleAmplifiersDeck->size() + _levelUpDeck->size()
                                                   + _specialMechanicsTreasureDeck->size() + _thingsAmplifiersDeck->size())){
        currentCard.first = true;
        currentCard.second = _thingsAmplifiersIterator->second.cardID();
        _thingsAmplifiersIterator++;
        _currCardsArrayRepresentationStep++;
    }
    else if (_currCardsArrayRepresentationStep < (_monstersDeck->size()
                                                   + _amplifiersDeck->size() + _cursesDeck->size()
                                                   + _professionsDeck->size() + _racesDeck->size()
                                                   + _specialMechanicsDeck->size()
                                                   + _armorDeck->size() + _armorAmplifiersDeck->size()
                                                   + _battleAmplifiersDeck->size() + _levelUpDeck->size()
                                                   + _specialMechanicsTreasureDeck->size() + _thingsAmplifiersDeck->size()
                                                   + _weaponsDeck->size())){
        currentCard.first = true;
        currentCard.second = _weaponsIterator->second.cardID();
        _weaponsIterator++;
        _currCardsArrayRepresentationStep++;
    }
    else {

        _monstersIterator = _monstersDeck->begin();
        _amplifiersIterator = _amplifiersDeck->begin();
        _cursesIterator = _cursesDeck->begin();
        _professionsIterator = _professionsDeck->begin();
        _racesIterator = _racesDeck->begin();
        _specialMechanicsIterator = _specialMechanicsDeck->begin();

        _armorIterator = _armorDeck->begin();
        _armorAmplifiersIterator = _armorAmplifiersDeck->begin();
        _battleAmplifiersIterator = _battleAmplifiersDeck->begin();
        _levelUpIterator = _levelUpDeck->begin();
        _specialMechanicsTreasureIterator = _specialMechanicsTreasureDeck->begin();
        _thingsAmplifiersIterator = _thingsAmplifiersDeck->begin();
        _weaponsIterator = _weaponsDeck->begin();

        currentCard.first = true;
        currentCard.second = _monstersIterator->second.cardID();
        _currCardsArrayRepresentationStep = 0;

        _doorsFold.clear();
        _treasuresFold.clear();
        ui->lbl_TreasuresFold->setText(QString::number(_treasuresFold.size()));
        ui->lbl_DoorsFold->setText(QString::number(_doorsFold.size()));
    }
//pass the Card;
    passTheCardToFoldStack(currentCard);
}

void CardStacks::startTheTest()
{
    if (!_testIsRunning)
    {
        _testTimer->start();
        _testIsRunning = true;
    }
    else
    {
        _testTimer->stop();
        _testIsRunning = false;
    }
}

QPoint CardStacks::ProvideTreasuresFoldPosition()
{
    return ui->btn_TreasuresFold->pos();
}

QPoint CardStacks::ProvideDoorsFoldPosition()
{
    return ui->btn_DoorsFold->pos();
}

QPoint CardStacks::ProvideTreasuresStackPosition()
{
    return ui->btn_TreasuresStack->pos();
}

QPoint CardStacks::ProvideDoorsStackPosition()
{
    return ui->btn_DoorsStack->pos();
}

QSize CardStacks::ProvideTreasuresFoldSize()
{
    return ui->btn_TreasuresFold->size();
}

QSize CardStacks::ProvideDoorsFoldSize()
{
    return ui->btn_DoorsFold->size();
}

void CardStacks::setMonsersDeck(const std::map<int, gameCardDoorMonster> *monsersDeck)
{
    _monstersDeck = monsersDeck;
}

void CardStacks::setAmplifiersDeck(const std::map<int, gameCardDoorAmplifier> *amplifiersDeck)
{
    _amplifiersDeck = amplifiersDeck;
}

void CardStacks::setCursesDeck(const std::map<int, gameCardDoorCurse> *cursesDeck)
{
    _cursesDeck = cursesDeck;
}

void CardStacks::setProfessionsDeck(const std::map<int, gameCardDoorProfession> *professionsDeck)
{
    _professionsDeck = professionsDeck;
}

void CardStacks::setRacesDeck(const std::map<int, gameCardDoorRace> *racesDeck)
{
    _racesDeck = racesDeck;
}

void CardStacks::setSpecialMechanicsDeck(const std::map<int, gameCardDoorSpecialMechanic> *specialMechanicsDeck)
{
    _specialMechanicsDeck = specialMechanicsDeck;
}

void CardStacks::setArmorDeck(const std::map<int, gameCardTreasureArmor> *armorDeck)
{
    _armorDeck = armorDeck;
}

void CardStacks::setArmorAmplifiersDeck(const std::map<int, gameCardTreasureArmorAmplifier> *armorAmplifiersDeck)
{
    _armorAmplifiersDeck = armorAmplifiersDeck;
}

void CardStacks::setBattleAmplifiersDeck(const std::map<int, gameCardTreasureBattleAmplifier> *battleAmplifiersDeck)
{
    _battleAmplifiersDeck = battleAmplifiersDeck;
}

void CardStacks::setLevelUpDeck(const std::map<int, gameCardTreasureLevelUp> *levelUpDeck)
{
    _levelUpDeck = levelUpDeck;
}

void CardStacks::setSpecialMechanicsTreasureDeck(const std::map<int, gameCardTreasureSpecialMechanic> *specialMechanicsTreasureDeck)
{
    _specialMechanicsTreasureDeck = specialMechanicsTreasureDeck;
}

void CardStacks::setThingsAmplifiersDeck(const std::map<int, gameCardTreasureThingsAmplifiers> *thingsAmplifiersDeck)
{
    _thingsAmplifiersDeck = thingsAmplifiersDeck;
}

void CardStacks::setWeaponsDeck(const std::map<int, gameCardTreasureWeapon> *weaponsDeck)
{
    _weaponsDeck = weaponsDeck;
}
