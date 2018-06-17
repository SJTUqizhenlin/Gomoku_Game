#include <iostream>
#include <string>
using namespace std;

class gameBoard{
private:
    const static int boardN = 15;
    int **arr;
public:
    gameBoard();
    ~gameBoard();
    void printBoard();
    bool add(const string &s, const int player);
    int** getBoard();
};

gameBoard::gameBoard(){
    arr = new int*[boardN];
    for (int i = 0; i < boardN; i++)
        arr[i] = new int[boardN];
    for (int i = 0; i < boardN; i++)
        for (int j = 0; j < boardN; j++)
            arr[i][j] = 0;
}

gameBoard::~gameBoard(){
    for (int i = 0; i < boardN; i++)
        delete [] arr[i];
    delete arr;
}

void gameBoard::printBoard(){
    cout << endl;
    cout << "  ";
    for (int j = 1; j <= 29; j++)
		if (j % 2 == 1) cout << (char)('a' + j / 2); 
        else cout << ' ';
	cout << endl;
    cout << endl;
	for (int i = 1; i <= 29; i++){
		if (i % 2 == 1){
			cout << (char)('a' + i / 2) << " ";
			for (int j = 1; j <= 29; j++){
				if (j % 2 == 1)
					if (arr[i / 2][j / 2] == 0) cout << ' ';
					else cout << (arr[i / 2][j / 2] == 1 ? 'O' : 'X');
				else cout << '-';
			}
		}
		else{
			cout << "  ";
			for (int j = 1; j <= 29; j++){
				if (j % 2 == 1) cout << '|';
				else cout << ' ';
			}
		}
		cout << endl;
	}
	return;
}

bool gameBoard::add(const string &s, const int player){
    if (s.length() != 2) return false;
    if (s[0] < 'a' || s[0] > 'o') return false;
    if (s[1] < 'a' || s[1] > 'o') return false;
    if (arr[s[0] - 'a'][s[1] - 'a'] != 0) return false;
    arr[s[0] - 'a'][s[1] - 'a'] = player;
    return true;
}

int** gameBoard::getBoard(){
    int **copy = new int*[boardN];
    for (int i = 0; i < boardN; i++){
        copy[i] = new int[boardN];
        for (int j = 0; j < boardN; j++)
            copy[i][j] = arr[i][j];
    }
    return copy;
}
