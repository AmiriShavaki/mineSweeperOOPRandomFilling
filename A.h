using namespace std;

const int xDir[8] = {-1, 0, 1, 1, 1, 0, -1, -1}, yDir[8] = {-1, -1, -1, 0, 1, 1, 1, 0};

class cell {
private:
    bool bomb;
    int neighborBombs;
    bool discovered;
public:
    cell();
    bool isBomb();
    void addNeighborBombs();
    bool isDiscovered();
    void setDiscovered();
    void setType(bool type);
    int getNeighborBombs();
};

class board {
private:
    int n;
    cell** mat;
    bool isFinished;
    int discoveredEmptyCells, totalEmptyCells;
public:
    board(int nn);
    void setType(int x, int y, bool type);
    bool getType(int x, int y);
    void fillRandom();
    void print(bool flg);
    void fillAttack();
    void printDebug();
    void setFinished();
    bool notFinished();
    void calculateTotalEmptyCells();
    void setDiscovered(int x, int y);
    int getDiscoveredEmptyCells();
    int getTotalEmptyCells();
};
