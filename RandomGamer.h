#ifndef SEABATTLE_RANDOMGAMER_H
#define SEABATTLE_RANDOMGAMER_H


#include "Gamer.h"

class RandomGamer: public Gamer {
public:
    explicit RandomGamer(int _order);
    void selectName() override;
    void setShips() override;
    bool move(Gamer &enemy) override;
};


#endif //SEABATTLE_RANDOMGAMER_H
