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

};

class HardCodedSettingsLimitations
{
public:

    static constexpr uint32_t totalCardsToGiveFromTheStart = 4;
    static constexpr uint32_t maximumCardsOnHandsInitialLimitation = 5;

};

#endif // MUNCHKINGLOBALDEFINES_H
