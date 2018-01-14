#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <set>
using namespace std;

struct coor {
    int row;
    int col;
};

int check(char board[][8], struct coor king, int colorMode)
{
    int row, col;
    int offset = colorMode * ('A' - 'a');
    char p, r, b, q, k, n;
    p = 'p' + offset;
    r = 'r' + offset;
    b = 'b' + offset;
    q = 'q' + offset;
    k = 'k' + offset;
    n = 'n' + offset;

    for(row = king.row, col = king.col - 1; col >= 0; col--){
        if(board[row][col] == r || board[row][col] == q)
            return 1;
        else if(board[row][col] == k && col == king.col - 1)
            return 1;
        else if(board[row][col] != '.')
            break;
    }
    for(row = king.row, col = king.col + 1; col < 8; col++){
        if(board[row][col] == r || board[row][col] == q)
            return 1;
        else if(board[row][col] == k && col == king.col + 1)
            return 1;
        else if(board[row][col] != '.')
            break;
    }
    for(row = king.row - 1, col = king.col; row >= 0; row--){
        if(board[row][col] == r || board[row][col] == q)
            return 1;
        else if(board[row][col] == k && row == king.row - 1)
            return 1;
        else if(board[row][col] != '.')
            break;
    }
    for(row = king.row + 1, col = king.col; row < 8; row++){
        if(board[row][col] == r || board[row][col] == q)
            return 1;
        else if(board[row][col] == k && row == king.row + 1)
            return 1;
        else if(board[row][col] != '.')
            break;
    }
    for(row = king.row - 1, col = king.col - 1; row >= 0 && col >= 0; row--, col--){
        if(board[row][col] == b || board[row][col] == q)
            return 1;
        else if((board[row][col] == k || board[row][col] == 'p' && colorMode == 0) 
                    && row == king.row - 1 && col == king.col - 1)
            return 1;
        else if(board[row][col] != '.')
            break;
    }
    for(row = king.row - 1, col = king.col + 1; row >= 0 && col < 8; row--, col++){
        if(board[row][col] == b || board[row][col] == q)
            return 1;
        else if((board[row][col] == k || board[row][col] == 'p' && colorMode == 0) 
                    && row == king.row - 1 && col == king.col + 1)
            return 1;
        else if(board[row][col] != '.')
            break;
    }
    for(row = king.row + 1, col = king.col + 1; row < 8 && col < 8; row++, col++){
        if(board[row][col] == b || board[row][col] == q)
            return 1;
        else if((board[row][col] == k || board[row][col] == 'P' && colorMode == 1) 
                    && row == king.row + 1 && col == king.col + 1)
            return 1;
        else if(board[row][col] != '.')
            break;
    }
    for(row = king.row + 1, col = king.col - 1; row < 8 && col >= 0; row++, col--){
        if(board[row][col] == b || board[row][col] == q)
            return 1;
        else if((board[row][col] == k || board[row][col] == 'P' && colorMode == 1) 
                    && row == king.row + 1 && col == king.col - 1)
            return 1;
        else if(board[row][col] != '.')
            break;
    }
    if(king.row - 1 >= 0 && king.col - 2 >= 0 && board[king.row - 1][king.col - 2] == n)
        return 1;
    if(king.row - 2 >= 0 && king.col - 1 >= 0 && board[king.row - 2][king.col - 1] == n)
        return 1;
    if(king.row - 2 >= 0 && king.col + 1 < 8 && board[king.row - 2][king.col + 1] == n)
        return 1;
    if(king.row - 1 >= 0 && king.col + 2 < 8 && board[king.row - 1][king.col + 2] == n)
        return 1;
    if(king.row + 1 < 8 && king.col + 2 < 8 && board[king.row + 1][king.col + 2] == n)
        return 1;
    if(king.row + 2 < 8 && king.col + 1 < 8 && board[king.row + 2][king.col + 1] == n)
        return 1;
    if(king.row + 2 < 8 && king.col - 1 >= 0 && board[king.row + 2][king.col - 1] == n)
        return 1;
    if(king.row + 1 < 8 && king.col - 2 >= 0 && board[king.row + 1][king.col - 2] == n)
        return 1;
    return 0;
}

int main() {
    int count = 0;
    while(1){
        char board[8][8];
        int stop = 1;
        struct coor blackKing;
        struct coor whiteKing;
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                cin >> board[i][j];
                if(board[i][j] != '.')
                    stop = 0;
                if(board[i][j] == 'k'){
                    blackKing.row = i;
                    blackKing.col = j;
                }
                if(board[i][j] == 'K'){
                    whiteKing.row = i;
                    whiteKing.col = j;
                }
            }
        }
        if(stop == 1)
            break;
        count++;;
        int whiteFlag = check(board, whiteKing, 0);
        int blackFlag = check(board, blackKing, 1);
        cout << "Game #" << count << ": ";
        if(whiteFlag == 1 && blackFlag == 0)
            cout << "white king is in check." << endl;
        else if(whiteFlag == 0 && blackFlag == 1)
            cout << "black king is in check." << endl;
        else if(whiteFlag == 0 && blackFlag == 0)
            cout << "no king is in check." << endl;
        else
            cout << "both king is in check. Error!" <<endl;
    }
    
}