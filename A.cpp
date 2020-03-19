#include <iostream>
#include "A.h"
#include <cstdlib>

using namespace std;

cell::cell() {
    discovered = false;
    neighborBombs = 0;
}

void cell::setDiscovered() {
    discovered = true;
}

void cell::setType(bool type) {
    bomb = type;
}

bool cell::isBomb() {
    return bomb;
}

board::board(int nn) {
    n = nn;
    mat = new cell*[n];
    for (int i = 0; i < n; i++) {
        mat[i] = new cell[n];
    }
    isFinished = false;
    discoveredEmptyCells = totalEmptyCells = 0;
}

void board::calculateTotalEmptyCells() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            totalEmptyCells += getType(j, i);
        }
    }
}

void board::setType(int x, int y, bool type) {
    (*(mat + y) + x) -> setType(type);
}

bool board::getType(int x, int y) {
    return (*(mat + y) + x) -> isBomb();
}
void board::fillRandom() {
    for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                setType(j, i, rand() % 10 != 1);
            }
    }
}

bool cell::isDiscovered() {
    return discovered;
}

void board::print(bool flg) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((*(mat + i) + j) -> isDiscovered()) {
                cout << (*(mat + i) + j) -> getNeighborBombs();
            } else if (flg && !((*(mat + i) + j) -> isBomb())) {
                cout << '*';
            } else {
                cout << '#';
            }
        }
        cout << endl;
    }
}

void board::setFinished() {
    isFinished = true;
}

bool board::notFinished() {
    return !isFinished;
}

int cell::getNeighborBombs() {
    return neighborBombs;
}

int board::getDiscoveredEmptyCells() {
    return discoveredEmptyCells;
}

int board::getTotalEmptyCells() {
    return totalEmptyCells;
}

void board::setDiscovered(int x, int y) {
    if (!((*(mat + y) + x) -> isDiscovered())) {
        (*(mat + y) + x) -> setDiscovered();
        if (((*(mat + y) + x) -> getNeighborBombs()) == 0) {
            for (int i = 0; i < 8; i++) {
                int newX = x + xDir[i], newY = y + yDir[i];
                if (newX < n && newX >= 0 && newY < n && newY >= 0 && getType(newX, newY)) {
                    setDiscovered(newX, newY);
                }
            }
        }
        discoveredEmptyCells++;
    }
}

void board::printDebug() {
    cout << "debug print:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
                cout << (getType(j, i) ? '#' : '*');
        }
        cout << endl;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
                cout << (*(mat + i) + j) -> getNeighborBombs();
        }
        cout << endl;
    }
}

void cell::addNeighborBombs() {
    neighborBombs++;
}

void board::fillAttack() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!getType(j, i)) {
                for (int i2 = 0; i2 < 8; i2++) {
                    int newX = j + xDir[i2], newY = i + yDir[i2];
                    if (newX < n && newX >= 0 && newY < n && newY >= 0 && getType(newX, newY)) {
                        (*(mat + newY) + newX) -> addNeighborBombs();
                    }
                }
            }
        }
    }
}
