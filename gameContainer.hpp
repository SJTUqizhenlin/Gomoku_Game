#include "gamePlayer.hpp"
#include "gameBoard.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

class gameContainer{
private:
    string ModuleName;
    gamePlayer *p1;
    gamePlayer *p2;
    gameBoard *bd;
public:
    gameContainer();
    void gameStart();
private:
    int gameJudge();
    const static int boardN = 15;
};

gameContainer::gameContainer(){
    string MN = "";
    while (MN != "cc" && MN != "hh" && MN != "hc"){
        cout << "Please choose the module of game: " << endl;
        cout << "Input 'cc' for computer-computer game" << endl;
        cout << "      'hh' for human-human game" << endl;
        cout << "      'hc' for human-computer battle" << endl;
        cin >> MN;
    }
    bd = new gameBoard();
    if (MN == "cc"){
        p1 = new gamePlayer("computer", 1);
        p2 = new gamePlayer("computer", 2);
    }
    if (MN == "hh"){
        p1 = new gamePlayer("human", 1);
        p2 = new gamePlayer("human", 2);
    }
    if (MN == "hc"){
        string f = "";
        while (f != "Yes" && f != "No"){
            cout << "Do you want to go fisrt?" << endl;
            cout << "Input 'Yes' or 'No'" << endl;
            cin >> f;
        }
        if (f == "Yes"){
            p1 = new gamePlayer("human", 1);
            p2 = new gamePlayer("computer", 2);
        }
        if (f == "No"){
            p1 = new gamePlayer("computer", 1);
            p2 = new gamePlayer("human", 2);
        }
    }
    cout << "Ready to start." << endl;
}

void gameContainer::gameStart(){
    int step = 0;
    string dc = "";
    int jd = 0;
    bd->printBoard();
    if (p1->getPlayerType() == "computer"){
        cout << "Next step: " << "hh" << endl; 
        bd->add("hh", 1);
    }
    else{
        dc = p1->makeDecision(bd->getBoard());
        cout << "Next step: " << dc << endl;
        bd->add(dc, 1);
    }
    system("pause");
    while (true){
        bd->printBoard();
        ++step;
        if (step % 2 == 0) dc = p1->makeDecision(bd->getBoard());
        else dc = p2->makeDecision(bd->getBoard());
        cout << "Next step: " << dc << endl;
        if (step % 2 == 0) bd->add(dc, 1);
        else bd->add(dc, 2);
        jd = gameJudge();
        if (jd > 0){
            bd->printBoard();
            if (jd == 1) 
                cout << "Player 1: " << p1->getPlayerType() << " win!" << endl;
            else
                cout << "Player 2: " << p2->getPlayerType() << " win!" << endl;
            break;
        }
        system("pause");
    }
    cout << "Game over." << endl; return;
}

int gameContainer::gameJudge(){
    int **arr = bd->getBoard();
    for (int i = 0; i < boardN; i++)
        for (int j = 0; j < boardN; j++){
            if (i + 4 < boardN && j + 4 < boardN){
                if (arr[i][j] == 1 && arr[i + 1][j + 1] == 1
                    && arr[i + 2][j + 2] == 1 && arr[i + 3][j + 3] == 1
                    && arr[i + 4][j + 4] == 1)
                    return 1;
                if (arr[i][j] == 2 && arr[i + 1][j + 1] == 2
                    && arr[i + 2][j + 2] == 2 && arr[i + 3][j + 3] == 2
                    && arr[i + 4][j + 4] == 2)
                    return 2;
            }
            if (i - 4 >= 0 && j + 4 < boardN){
                if (arr[i][j] == 1 && arr[i - 1][j + 1] == 1
                    && arr[i - 2][j + 2] == 1 && arr[i - 3][j + 3] == 1
                    && arr[i - 4][j + 4] == 1)
                    return 1;
                if (arr[i][j] == 2 && arr[i - 1][j + 1] == 2
                    && arr[i - 2][j + 2] == 2 && arr[i - 3][j + 3] == 2
                    && arr[i - 4][j + 4] == 2)
                    return 2;
            }
            if (i + 4 < boardN){
                if (arr[i][j] == 1 && arr[i + 1][j] == 1
                    && arr[i + 2][j] == 1 && arr[i + 3][j] == 1
                    && arr[i + 4][j] == 1)
                    return 1;
                if (arr[i][j] == 2 && arr[i + 1][j] == 2
                    && arr[i + 2][j] == 2 && arr[i + 3][j] == 2
                    && arr[i + 4][j] == 2)
                    return 2;
            }
            if (j + 4 < boardN){
                if (arr[i][j] == 1 && arr[i][j + 1] == 1
                    && arr[i][j + 2] == 1 && arr[i][j + 3] == 1
                    && arr[i][j + 4] == 1)
                    return 1;
                if (arr[i][j] == 2 && arr[i][j + 1] == 2
                    && arr[i][j + 2] == 2 && arr[i][j + 3] == 2
                    && arr[i][j + 4] == 2)
                    return 2;
            }
        }
    return 0;
}