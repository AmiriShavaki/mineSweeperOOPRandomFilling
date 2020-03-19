#include "A.h"
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    board game(n);
    game.fillRandom();
    game.fillAttack();
    game.calculateTotalEmptyCells();
    bool win;
    while (game.notFinished()) {
        game.print(false);
        int x, y;
        cin >> x >> y;
        if (game.getType(x, y)) {
            game.setDiscovered(x, y);
        } else {
            game.setFinished();
            win = false;
        }
        if (game.getDiscoveredEmptyCells() == game.getTotalEmptyCells()) {
            game.setFinished();
            win = true;
        }
    }
    if (win) {
        game.print(false);
        cout << "congratulations!";
    } else {
        game.print(true);
        cout << "hey you are a big looser!";
    }
}
