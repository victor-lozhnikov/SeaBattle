#ifndef SEABATTLE_SMARTGAMER_H
#define SEABATTLE_SMARTGAMER_H


#include "Gamer.h"

class SmartGamer: public Gamer {
public:
    explicit SmartGamer(int _order);
    void selectName() override;
    void setShips() override;
    bool move(Gamer &enemy) override;

};


#endif //SEABATTLE_SMARTGAMER_H
