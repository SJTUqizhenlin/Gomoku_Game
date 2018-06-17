#include <iostream>
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

class gamePlayer{
private:
    string playerType; // 'computer' or 'human'
    int playerNum; // 1 or 2
    int **curArr; // copy of board
    const static int boardN = 15;
    const static int maxDep = 7;
public:
    string getPlayerType();
    int getPlayerNum();
    gamePlayer(const string &type, int num);
    ~gamePlayer();
    string makeDecision(int **arr);
    string computerDecision();
private:
    const int randbeg[2] = {0, boardN * boardN - 1};
    const int randdij[2] = {1, -1};
    bool isGoodPlace(int i, int j);
    int scoreIt();
    int countContiniousR(int x, int y, int pnum);
    int countContiniousD(int x, int y, int pnum);
    int countContiniousRD(int x, int y, int pnum);
    int countContiniousRU(int x, int y, int pnum);
    int dfs(int boundary, int dep);
};

string gamePlayer::getPlayerType(){ return playerType; }

int gamePlayer::getPlayerNum(){ return playerNum; }

gamePlayer::gamePlayer(const string &type, int num){
    playerType = "";
    srand((unsigned)(time(0)));
    int rd = rand();
    if (type == "computer") playerType = "computer";
    if (type == "human") playerType = "human";
    playerNum = num;
    if (playerType == "") 
        throw "Wrong Player Type!";
    curArr = new int*[boardN];
    for (int i = 0; i < boardN; i++)
        curArr[i] = new int[boardN];
}

gamePlayer::~gamePlayer(){
    for (int i = 0; i < boardN; i++)
        delete [] curArr[i];
    delete curArr;
}

string gamePlayer::makeDecision(int **arr){
    for (int i = 0; i < boardN; i++)
        for (int j = 0; j < boardN; j++)
            curArr[i][j] = arr[i][j];
    for (int i = 0; i < boardN; i++) delete [] arr[i];
    delete arr;
    if (playerType == "human"){
        string s = "";
        while (true){
            cout  << "Human player, please make your decision" << endl;
            cin >> s;
            if (s[0] >= 'a' && s[0] <= 'o' 
                && s[1] >= 'a' && s[1] <= 'o'
                && s.length() == 2)
                if (curArr[s[0] - 'a'][s[1] - 'a'] == 0) break;
        }
        return s;
    }
    else return this->computerDecision();
}

string gamePlayer::computerDecision(){
    int val = INT32_MIN;
    int tarx = -1, tary = -1;
    for (int i = 0; i < boardN; i++)
        for (int j = 0; j < boardN; j++)
            if (curArr[i][j] == 0){
                tarx = i; tary = j;
                break;
            }
    int i, j;
    int ijbeg, ijend, dij;
    int rd = rand();
    ijbeg = randbeg[rd % 2];
    dij = randdij[rd % 2];
    ijend = randbeg[1 - (rd % 2)] + dij;
    for (int ij = ijbeg; ij != ijend; ij += dij){
        i = ij / boardN; j = ij % boardN;
        if (isGoodPlace(i, j)){
            curArr[i][j] = playerNum;
            int res = dfs(val, 1);
            curArr[i][j] = 0;
            if (res > val) {
                val = res;
                tarx = i; tary = j;
            }
        }
    }
    string s = "zz";
    s[0] = (char)(tarx + 'a');
    s[1] = (char)(tary + 'a');
    return s;
}

bool gamePlayer::isGoodPlace(int i, int j){
    if (curArr[i][j] != 0) return false;
    int c = 0;
    for (int dx = -1; dx <= 1; dx++)
        for (int dy = -1; dy <= 1; dy++)
            if (i + dx >= 0 && i + dx < boardN
                && j + dy >= 0 && j + dy < boardN)
                c += (curArr[i + dx][j + dy] != 0);
    return (c > 0);
}

int gamePlayer::dfs(int boundary, int dep){
    int sc = scoreIt();
    if (dep == maxDep) return sc;
    if (sc == INT32_MAX || sc == INT32_MIN)
        return sc;
    int i, j, res, val = sc;
    if (dep % 2 == 1){
        int ijbeg, ijend, dij;
        int rd = rand();
        ijbeg = randbeg[rd % 2];
        dij = randdij[rd % 2];
        ijend = randbeg[1 - (rd % 2)] + dij;
        for (int ij = ijbeg; ij != ijend; ij += dij){
            i = ij / boardN; j = ij % boardN;
            if (isGoodPlace(i, j)){
                curArr[i][j] = 3 - playerNum;
                res = dfs(val, dep + 1);
                curArr[i][j] = 0;
                if (res < val) val = res;
                if (val <= boundary) break;
            }
        }
        return val;
    }
    else{
        int ijbeg, ijend, dij;
        int rd = rand();
        ijbeg = randbeg[rd % 2];
        dij = randdij[rd % 2];
        ijend = randbeg[1 - (rd % 2)] + dij;
        for (int ij = ijbeg; ij != ijend; ij += dij){
            i = ij / boardN; j = ij % boardN;
            if (isGoodPlace(i, j)){
                curArr[i][j] = playerNum;
                res = dfs(val, dep + 1);
                curArr[i][j] = 0;
                if (res > val) val = res;
                if (val >= boundary) break;
            }
        }
        return val;
    }
}

int gamePlayer::scoreIt(){
    int ccArr[6] = {0, 0, 0, 0, 0, 0};
    int p;
    for (int i = 0; i < boardN; i++)
        for (int j = 0; j < boardN; j++)
            if (curArr[i][j] != 0){
                p = (curArr[i][j] == playerNum ? 1 : -1);
                ccArr[countContiniousR(i, j, curArr[i][j])] += p;
                ccArr[countContiniousD(i, j, curArr[i][j])] += p;
                ccArr[countContiniousRD(i, j, curArr[i][j])] += p;
                ccArr[countContiniousRU(i, j, curArr[i][j])] += p;
            }
    if (ccArr[5] > 0) return INT32_MAX;
    if (ccArr[5] < 0) return INT32_MIN;
    if (ccArr[4] > 0) return (1 << 20) - 1;
    if (ccArr[4] < 0) return 0 - (1 << 20);
    if (ccArr[3] > 0) return (1 << 10) - 1;
    if (ccArr[3] < 0) return 0 - (1 << 10);
    if (ccArr[2] > 0) return (1 << 1) - 1;
    if (ccArr[2] < 0) return 0 - (1 << 1);
    return 0;
}

int gamePlayer::countContiniousR(int i, int j, int pnum){
    if (j > 0 && curArr[i][j - 1] == pnum) return 0;
    int d = 0;
    while (j + d < boardN){
        if (curArr[i][j + d] != pnum) break; 
        ++d;
    }
    if (d >= 5) return 5;
    if (j - 1 >= 0 && j + d < boardN){
        if (curArr[i][j - 1] != 0 && curArr[i][j + d] != 0) 
            return 0;
        if (curArr[i][j - 1] != 0 && curArr[i][j + d] == 0)
            return (d - 1);
        if (curArr[i][j - 1] == 0 && curArr[i][j + d] != 0) 
            return (d - 1); 
        return d;
    }
    if (j - 1 < 0){
        if (curArr[i][j + d] != 0) return 0;
        return (d - 1);
    }
    if (curArr[i][j - 1] != 0) return 0;
    return (d - 1);
}

int gamePlayer::countContiniousD(int i, int j, int pnum){
    if (i > 0 && curArr[i - 1][j] == pnum) return 0;
    int d = 0;
    while (i + d < boardN){
        if (curArr[i + d][j] != pnum) break; 
        ++d;
    }
    if (d >= 5) return 5;
    if (i - 1 >= 0 && i + d < boardN){
        if (curArr[i - 1][j] != 0 && curArr[i + d][j] != 0) 
            return 0;
        if (curArr[i - 1][j] != 0 && curArr[i + d][j] == 0)
            return (d - 1);
        if (curArr[i - 1][j] == 0 && curArr[i + d][j] != 0) 
            return (d - 1); 
        return d;
    }
    if (i - 1 < 0){
        if (curArr[i + d][j] != 0) return 0;
        return (d - 1);
    }
    if (curArr[i - 1][j] != 0) return 0;
    return (d - 1);
}

int gamePlayer::countContiniousRD(int i, int j, int pnum){
    if ((j > 0 && i > 0) && curArr[i - 1][j - 1] == pnum) return 0;
    int d = 0;
    while (j + d < boardN && i + d < boardN){
        if (curArr[i + d][j + d] != pnum) break; 
        ++d;
    }
    if (d >= 5) return 5;
    if ((j - 1 >= 0 && i - 1 >= 0) && (j + d < boardN && i + d < boardN)){
        if (curArr[i - 1][j - 1] != 0 && curArr[i + d][j + d] != 0) 
            return 0;
        if (curArr[i - 1][j - 1] != 0 && curArr[i + d][j + d] == 0)
            return (d - 1);
        if (curArr[i - 1][j - 1] == 0 && curArr[i + d][j + d] != 0) 
            return (d - 1); 
        return d;
    }
    if ((j - 1 < 0 || i - 1 < 0) && (j + d >= boardN || i + d >= boardN))
        return 0;
    if (j - 1 < 0 || i - 1 < 0){
        if (curArr[i + d][j + d] != 0) return 0;
        return (d - 1);
    }
    if (curArr[i - 1][j - 1] != 0) return 0;
    return (d - 1);
}

int gamePlayer::countContiniousRU(int i, int j, int pnum){
    if ((j > 0 && i < boardN - 1) && curArr[i + 1][j - 1] == pnum) return 0;
    int d = 0;
    while (j + d < boardN && i - d >= 0){
        if (curArr[i - d][j + d] != pnum) break; 
        ++d;
    }
    if (d >= 5) return 5;
    if ((j - 1 >= 0 && i < boardN - 1) && (j + d < boardN && i - d >= 0)){
        if (curArr[i + 1][j - 1] != 0 && curArr[i - d][j + d] != 0) 
            return 0;
        if (curArr[i + 1][j - 1] != 0 && curArr[i - d][j + d] == 0)
            return (d - 1);
        if (curArr[i + 1][j - 1] == 0 && curArr[i - d][j + d] != 0) 
            return (d - 1); 
        return d;
    }
    if ((j - 1 < 0 || i >= boardN - 1) && (j + d >= boardN || i - d < 0))
        return 0;
    if (j - 1 < 0 || i >= boardN - 1){
        if (curArr[i - d][j + d] != 0) return 0;
        return (d - 1);
    }
    if (curArr[i + 1][j - 1] != 0) return 0;
    return (d - 1);
}