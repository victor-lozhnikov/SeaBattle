#ifndef SEABATTLE_GAMER_H
#define SEABATTLE_GAMER_H

#include <string>
#include <vector>

class Gamer {
public:
    explicit Gamer(int _order);
    std::string getName() const;
    std::vector<std::vector<int>> getField () const;
    bool isReady() const;
    int getAvailableShips(int shipLen) const;
    void removeAll();
    int getWinCount() const;
    void addWin();
    int getOrder() const;
    int shot (std::string s, int* sx, int* sy);
    bool isKilled () const;
    void setName(const std::string &_name);
    bool addShip (std::string start, std::string end);
    void randomSetShips ();
    void smartSetShips ();
    bool randomMove(int* sx, int* sy);
    bool smartMove(int* sx, int* sy);

    virtual void selectName() = 0;
    virtual void setShips() = 0;
    virtual bool move(Gamer &enemy) = 0;

private:
    std::string name;
    std::vector<std::vector<int>> field;
    std::vector <int> shipCount;
    std::vector <int> shipAvailable;
    std::vector <std::vector <std::pair <int, int>>> ships;
    int winCount;
    int order;
    void markNeighbours(const int &i, const int &j);
    void markKilledShipNeighbours (std::vector<std::pair <int, int>> &ship);
    std::vector <std::pair <int, int>> getShipByCoord (std::pair <int, int>) const;
};


#endif //SEABATTLE_GAMER_H
