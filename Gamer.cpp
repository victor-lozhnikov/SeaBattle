#include <algorithm>
#include <string>
#include <iostream>
#include <cstdlib>
#include "Gamer.h"

/*
 -1 - недоступна для расстановки
 0 - пустая
 1 - занята кораблем
 2 - прострелена
 3 - простреленный корабль
 4 - убитый корабль
*/

Gamer::Gamer() {
    field.assign(12, std::vector<int> (12, 0));
    shipCount.assign(4, 0);
    shipAvailable = {4, 3, 2, 1};
    winCount = 0;
}

int Gamer::getWinCount() const {
    return winCount;
}

void Gamer::addWin() {
    winCount++;
}

std::string Gamer::getName() const {
    return name;
}

void Gamer::setName(const std::string &_name) {
    name = _name;
}

bool Gamer::isKilled() {
    for (auto &i : field) {
        for (auto &j : i) {
            if (j == 1) {
                return false;
            }
        }
    }
    return true;
}

std::vector<std::vector<int>> Gamer::getField() const {
    return field;
}

bool Gamer::addShip(std::string start, std::string end) {
    if (start.size() != 2 || end.size() != 2) {
        return false;
    }

    start[0] = tolower(start[0]);
    end[0] = tolower(end[0]);

    if (start[0] < 'a' || start[0] > 'j' || end[0] < 'a' || end[0] > 'j') {
        return false;
    }
    if (start[1] < '0' || start[1] > '9' || end[1] < '0' || end[1] > '9') {
        return false;
    }

    int shipLen;
    std::vector <std::pair<int, int>> ship;
    if (start[0] == end[0]) {
        shipLen = abs(start[1] - end[1]);
        if (shipLen > 3) {
            return false;
        }
        if (shipCount[shipLen] == shipAvailable[shipLen]) {
            return false;
        }

        if (start[1] > end[1]) {
            start.swap(end);
        }
        int y = start[0] - 'a' + 1;
        for (int i = start[1] - '0' + 1; i <= end[1] - '0' + 1; ++i) {
            if (field[i][y] != 0) {
                return false;
            }
        }
        for (int i = start[1] - '0' + 1; i <= end[1] - '0' + 1; ++i) {
            field[i][y] = 1;
            markNeighbours(i, y);
            ship.emplace_back(std::make_pair(i, y));
        }
        shipCount[shipLen]++;
        ships.emplace_back(ship);
    }
    else if (start[1] == end[1]) {
        shipLen = abs(start[0] - end[0]);
        if (shipLen > 3) {
            return false;
        }
        if (shipCount[shipLen] == shipAvailable[shipLen]) {
            return false;
        }

        if (start[0] > end[0]) {
            start.swap(end);
        }
        int x = start[1] - '0' + 1;
        for (int i = start[0] - 'a' + 1; i <= end[0] - 'a' + 1; ++i) {
            if (field[x][i] != 0) {
                return false;
            }
        }
        for (int i = start[0] - 'a' + 1; i <= end[0] - 'a' + 1; ++i) {
            field[x][i] = 1;
            ship.emplace_back(std::make_pair(x, i));
            markNeighbours(x, i);
        }
        shipCount[shipLen]++;
        ships.emplace_back(ship);
    }
    else {
        return false;
    }
    return true;
}

bool Gamer::isReady() {
    for (int i = 0; i < 4; ++i) {
        if (shipCount[i] != shipAvailable[i]) {
            return false;
        }
    }
    return true;
}

void Gamer::markNeighbours(const int &i, const int &j) {
    for (int ii = -1; ii <= 1; ++ii) {
        for (int jj = -1; jj <= 1; ++jj) {
            if (field[i + ii][j + jj] == 0) {
                field[i + ii][j + jj] = -1;
            }
        }
    }
}

void Gamer::markKilledShipNeighbours(std::vector<std::pair<int, int>> &ship) {
    for (auto &i : ship) {
        for (int ii = -1; ii <= 1; ++ii) {
            for (int jj = -1; jj <= 1; ++jj) {
                if (field[i.first + ii][i.second + jj] == -1) {
                    field[i.first + ii][i.second + jj] = 2;
                }
            }
        }
    }
}

int Gamer::getAvailableShips(int shipLen) {
    return shipAvailable[shipLen - 1] - shipCount[shipLen - 1];
}

void Gamer::removeAll() {
    field.assign(12, std::vector<int> (12, 0));
    shipCount.assign(4, 0);
}

void Gamer::randomSetShips() {
    srand(time(nullptr));
    for (int i = 3; i >= 0; --i) {
        for (int j = shipCount[i]; j < shipAvailable[i]; ++j) {
            bool ok = false;
            while (!ok) {
                int s1, s2, dir;
                s1 = rand() % (10 - i);
                s2 = rand() % (10 - i);
                dir = rand() % 2;
                std::string start, end;
                start += (char)(s1 + 'a');
                start += (char)(s2 + '0');
                if (dir) {
                    end += (char)(s1 + i + 'a');
                    end += (char)(s2 + '0');
                }
                else {
                    end += (char)(s1 + 'a');
                    end += (char)(s2 + i + '0');
                }


                if (addShip(start, end)) {
                    ok = true;
                }
            }
        }
    }
}

void Gamer::smartSetShips() {
    srand(time(nullptr));
    for (int i = 3; i > 0; --i) {
        for (int j = shipCount[i]; j < shipAvailable[i]; ++j) {
            bool ok = false;
            while (!ok) {
                int s1, s2;
                s1 = rand() % 4;
                s2 = rand() % (10 - i);
                std::string start, end;
                if (s1 == 0) {
                    start += 'a';
                    start += (char)(s2 + '0');
                    end += 'a';
                    end += (char)(s2 + i + '0');
                }
                else if (s1 == 1) {
                    start += 'j';
                    start += (char)(s2 + '0');
                    end += 'j';
                    end += (char)(s2 + i + '0');
                }
                else if (s1 == 2) {
                    start += (char)(s2 + 'a');
                    start += '0';
                    end += (char)(s2 + i + 'a');
                    end += '0';
                }
                else {
                    start += (char)(s2 + 'a');
                    start += '9';
                    end += (char)(s2 + i + 'a');
                    end += '9';
                }

                if (addShip(start, end)) {
                    ok = true;
                }
            }
        }
    }
    for (int j = shipCount[0]; j < shipAvailable[0]; ++j) {
        bool ok = false;
        while (!ok) {
            int s1, s2;
            s1 = rand() % 10;
            s2 = rand() % 10;
            std::string start;
            start += (char)(s1 + 'a');
            start += (char)(s2 + '0');

            if (addShip(start, start)) {
                ok = true;
            }
        }
    }
}

std::vector <std::pair <int, int>> Gamer::getShipByCoord(std::pair<int, int> coords) {
    for (auto &i : ships) {
        for (auto &j : i) {
            if (j == coords) {
                return i;
            }
        }
    }
    return std::vector<std::pair<int, int>>();
}

/*
-1 - некорректный ввод
0 - промах
1 - попал
*/
int Gamer::shot(std::string s, int* sx, int* sy) {
    int y = s[0] - 'a' + 1;
    int x = s[1] - '0' + 1;
    if (x < 1 || x > 10 || y < 1 || y > 10) {
        return -1;
    }
    if (field[x][y] > 1) {
        return -1;
    }
    field[x][y] = std::max(2, field[x][y] + 2);
    *sx = x;
    *sy = y;
    if (field[x][y] != 3) {
        return 0;
    }
    std::vector <std::pair <int, int>> ship = getShipByCoord(std::make_pair(x, y));
    bool killed = true;
    for (auto &i : ship) {
        if (field[i.first][i.second] != 3) {
            killed = false;
            break;
        }
    }

    if (!killed) {
        return 1;
    }
    markKilledShipNeighbours(ship);
    for (auto &i : ship) {
        field[i.first][i.second] = 4;
    }
    return 1;
}

bool Gamer::randomMove(int* sx, int* sy) {
    srand(time(nullptr));
    bool ok = false;
    int shotRes = -1;
    while (!ok) {
        int x = rand() % 10;
        int y = rand() % 10;
        std::string s;
        s += (char)(x + 'a');
        s += (char)(y + '0');
        shotRes = shot(s, sx, sy);
        if (shotRes == -1) {
            continue;
        }
        ok = true;
    }
    return (shotRes == 1);
}

bool Gamer::smartMove(int *sx, int *sy) {
    bool notKilled = false;
    std::vector <std::pair <int, int>> coordsToKill;
    for (int i = 1; i <= 10; ++i) {
        for (int j = 1; j <= 10; ++j) {
            if (field[i][j] == 3) {
                notKilled = true;
                coordsToKill.emplace_back(std::make_pair(i, j));
            }
        }
    }
    if (!notKilled) {
        return randomMove(sx, sy);
    }

    int x = coordsToKill[0].first;
    int y = coordsToKill[0].second;
    std::string s;

    if (coordsToKill.size() == 1) {
        if (field[x-1][y] < 2 && x > 1) {
            s += (char)(y - 1 + 'a');
            s += (char)(x - 2 + '0');
        }
        else if (field[x+1][y] < 2 && x < 10) {
            s += (char)(y - 1 + 'a');
            s += (char)(x + '0');
        }
        else if (field[x][y-1] < 2 && y > 1) {
            s += (char)(y - 2 + 'a');
            s += (char)(x - 1 + '0');
        }
        else if (field[x][y+1] < 2 && y < 10) {
            s += (char)(y + 'a');
            s += (char)(x - 1 + '0');
        }
        int shotRes = shot(s, sx, sy);
        return (shotRes == 1);
    }

    if (coordsToKill[0].first == coordsToKill[1].first) {
        if (field[x][y-1] < 2 && y > 1) {
            s += (char)(y - 2 + 'a');
        }
        else {
            int y1 = coordsToKill.back().second;
            s += (char)(y1 + 'a');
        }
        s += (char)(x - 1 + '0');
    }
    else {
        s += (char)(y - 1 + 'a');
        if (field[x-1][y] < 2 && x > 1) {
            s += (char)(x - 2 + '0');
        }
        else {
            int x1 = coordsToKill.back().first;
            s += (char)(x1 + '0');
        }
    }
    int shotRes = shot(s, sx, sy);
    return (shotRes == 1);
}