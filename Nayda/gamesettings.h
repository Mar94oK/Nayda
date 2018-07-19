#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H


class GameSettings
{
    /* Time to decide what action to take - sold some cards,
     *                                      make collaborations
     *                                      play card from hands
     *                                      play card from Monster's (Doors) Deck
    */
    unsigned int _timeToThinkBeforeMove;

    unsigned int _timeToCollaborate;
    unsigned int _timeToMakeOpposedMove;



public:
    GameSettings();
};

#endif // GAMESETTINGS_H
