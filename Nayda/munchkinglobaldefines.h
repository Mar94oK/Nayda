#ifndef MUNCHKINGLOBALDEFINES_H
#define MUNCHKINGLOBALDEFINES_H

#ifdef Q_OS_WIN
#define USE_RESOURCES
#elif defined __linux__
#define USE_RESOURCES
#endif


class GeometricLimitations {

public:

    static constexpr float beforeTheGameWindowsSize = 0.5f;
    static constexpr float beforeTheGameButtonsSize = 0.1f;

//Related to CardsOnHand (Hand) widget;

    static constexpr float handCardSize_width_to_height_ratio = 2.71f;
    static constexpr float handCardSizeWidht = 0.019f;
    static constexpr float handCardSizeHeight = handCardSize_width_to_height_ratio*handCardSizeWidht;

//Related to CardsInGame widget;

    static constexpr float cardInGametoCardOnHandSizeRatio = 0.3333333f;

};

class HardCodedSettingsLimitations
{
public:

    static constexpr uint32_t totalCardsToGiveFromTheStart = 4;
    static constexpr uint32_t maximumCardsOnHandsInitialLimitation = 5;

};



#endif // MUNCHKINGLOBALDEFINES_H
