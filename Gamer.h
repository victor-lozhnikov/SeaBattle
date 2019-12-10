#ifndef SEABATTLE_GAMER_H
#define SEABATTLE_GAMER_H

#include <string>
#include <vector>

class Gamer {
public:
    Gamer();
    std::string getName() const;
    void setName(const std::string &_name);
    std::vector<std::vector<int>> getField () const;
    bool addShip (std::string start, std::string end);
    bool isReady();
    void markNeighbours(const int &i, const int &j);
    void markKilledShipNeighbours (std::vector<std::pair <int, int>> &ship);
    int getAvailableShips(int shipLen);
    void removeAll();
    void randomSetShips ();
    void smartSetShips ();
    bool isKilled ();
    int shot (std::string s, int* sx, int* sy);
    std::vector <std::pair <int, int>> getShipByCoord (std::pair <int, int>);
    bool randomMove(int* sx, int* sy);
    bool smartMove(int* sx, int* sy);
    int getWinCount() const;
    void addWin();

private:
    std::string name;
    std::vector<std::vector<int>> field;
    std::vector <int> shipCount;
    std::vector <int> shipAvailable;
    std::vector <std::vector <std::pair <int, int>>> ships;
    int winCount;
};


#endif //SEABATTLE_GAMER_H
