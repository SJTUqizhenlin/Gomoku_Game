#include <iostream>
#include <string>
#include <stdlib.h>
#include "gameContainer.hpp"
using namespace std;

int main(){
    cout << "Welcome to Gomoku Game!" << endl;
    gameContainer *game = new gameContainer();
    game->gameStart();
    cout << "Thanks for gaming." << endl;
    system("pause");
    return 0;
}