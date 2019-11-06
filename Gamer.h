#ifndef SEABATTLE_GAMER_H
#define SEABATTLE_GAMER_H

#include <string>
#include <vector>

class Gamer {
public:
    Gamer();
    std::string getName();
    void setName(const std::string &_name);
    std::vector<std::vector<int>> getField () const;
    bool addShip (std::string start, std::string end);
    bool isReady();
    bool checkPoint (const int &i, const int &j);
    void markNeighbours(const int &i, const int &j);
    int getAvailableShips(int shipLen);
    void removeAll();
    void randomSetShips ();

private:
    std::string name;
    std::vector<std::vector<int>> field;
    std::vector <int> shipCount;
    std::vector <int> shipAvailable;
};


#endif //SEABATTLE_GAMER_H
