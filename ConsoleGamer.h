#ifndef SEABATTLE_CONSOLEGAMER_H
#define SEABATTLE_CONSOLEGAMER_H


#include "Gamer.h"

class ConsoleGamer: public Gamer {
public:
    explicit ConsoleGamer(int _order);
    void selectName() override;
    void setShips() override;
    bool move(Gamer &enemy) override;
};


#endif //SEABATTLE_CONSOLEGAMER_H
