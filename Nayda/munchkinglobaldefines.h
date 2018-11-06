#ifndef MUNCHKINGLOBALDEFINES_H
#define MUNCHKINGLOBALDEFINES_H

#ifdef Q_OS_WIN
#undef USE_RESOURCES
#elif defined __linux__
#define USE_RESOURCES
#endif

class GeometricLimitations {

public:

    static constexpr float beforeTheGameWindowsSize = 0.5f;
    static constexpr float beforeTheGameButtonsSize = 0.1f;

};

#endif // MUNCHKINGLOBALDEFINES_H
