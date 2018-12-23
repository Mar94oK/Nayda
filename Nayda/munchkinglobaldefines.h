#ifndef MUNCHKINGLOBALDEFINES_H
#define MUNCHKINGLOBALDEFINES_H

#ifdef Q_OS_WIN
#define USE_RESOURCES
#elif defined __linux__
#define USE_RESOURCES
#endif

#include <stdint.h>

class GeometricLimitations {

public:

    static constexpr float beforeTheGameWindowsSize = 0.5f;
    static constexpr float beforeTheGameButtonsSize = 0.1f;

//Related to CardsOnHand (Hand) widget;

    static constexpr float handcardsizeWidthToHeightRatio = 2.71f;
    static constexpr float handCardSizeWidht = 0.019f;
    static constexpr float handCardSizeHeight = handcardsizeWidthToHeightRatio*handCardSizeWidht;

    static constexpr float handCardMainGamerSizeRatio = 2.0f;

//Related to CardsInGame widget;

    static constexpr float cardInGametoCardOnHandSizeRatio = 1.3333333f;

    //Related to GamerWidget commons (level picture, battlePower picture, etc...)
    static constexpr float cardGamerWidgetSizeRatio = 1.65f;

//Related to CardStacksWidget;

    static constexpr float cardCardStacksWidgetSizeRatio = 2;
};

class HardCodedSettingsLimitations
{
public:

    static constexpr uint32_t totalCardsToGiveFromTheStart = 4;
    static constexpr uint32_t maximumCardsOnHandsInitialLimitation = 5;

};

class AnimationPhasesLimitations
{

public:

    static constexpr uint32_t msTimeToHoldCardWhileAddingCardToCardsInGame = 1000;
};

class GamerWidgetPerfomanceValues
{

public:

    static constexpr uint32_t totalOpponentsAtTopLayout = 2;
};

class CardsInGameWidgetPerfomanceValues
{

public:

    static constexpr uint32_t maximumCardsInARowInTheCardsInActiveGameLayout = 5;

    static constexpr bool threeLayoutForCardsAreEnabled = false;
};

#endif // MUNCHKINGLOBALDEFINES_H
