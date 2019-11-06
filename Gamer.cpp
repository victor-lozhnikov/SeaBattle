#include <algorithm>
#include <string>
#include <iostream>
#include <cstdlib>
#include "Gamer.h"

Gamer::Gamer() {
    field.assign(12, std::vector<int> (12, 0));
    shipCount.assign(4, 0);
    shipAvailable = {4, 3, 2, 1};
}

std::string Gamer::getName() {
    return name;
}

void Gamer::setName(const std::string &_name) {
    name = _name;
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
        }
        shipCount[shipLen]++;
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
            markNeighbours(x, i);
        }
        shipCount[shipLen]++;
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

bool Gamer::checkPoint(const int &i, const int &j) {
    for (int ii = -1; ii <= 1; ++ii) {
        for (int jj = -1; jj <= 1; ++jj) {
            if (field[i + ii][j + jj] == 1) {
                return false;
            }
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