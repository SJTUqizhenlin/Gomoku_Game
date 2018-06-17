#include "gameBoard.hpp"
#include "gamePlayer.hpp"
#include <stdlib.h>

void test1(){
    gameBoard *b = new gameBoard();
    b->printBoard();
    string order;
    while (1){
        cin >> order;
        if (order == "end") break;
        while (!(b->add(order, 2)))
            cin >> order;
        b->printBoard();
    }
    int **c = b->getBoard();
    cout << c[7][7];
    delete b;
    return;
}

void test2(){
    gamePlayer *p = new gamePlayer("computer", 2);
    gameBoard *b = new gameBoard();
    b->add("hh", 2);
    b->add("hg", 2);
    b->add("hi", 2);
    b->add("hf", 1);
    string s = p->makeDecision(b->getBoard());
    cout << s << endl;
    b->add(s, 2);
    b->printBoard();
    delete b; delete p;
    return;
}

int main(){
    //test1();
    test2();
    system("pause");
    return 0;
}