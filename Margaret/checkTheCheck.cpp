#include <iostream>
#include <cstring>

using namespace std;

#define SIZE 8

char Board[SIZE][SIZE];
int kx, ky, Kx, Ky; // position of two kings

bool IsValid(int x, int y)
{
    return (x >= 0 && x < SIZE && y >= 0 && y < SIZE);
}

bool Match(int x, int y, char c)
{
    return (IsValid(x, y) && Board[x][y] == c);
}

char checkPp()
{
    if (Match(kx + 1, ky + 1, 'P') || Match(kx + 1, ky - 1, 'P'))
        return '1';

    if (Match(Kx - 1, Ky - 1, 'p') || Match(Kx - 1, Ky + 1, 'p'))
        return '0';

    return '2';
}

char checkKk()
{
    if (Match(kx + 1, ky - 2, 'N') || Match(kx - 1, ky - 2, 'N') ||
        Match(kx + 1, ky + 2, 'N') || Match(kx - 1, ky + 2, 'N') ||
        Match(kx + 2, ky - 1, 'N') || Match(kx - 2, ky - 1, 'N') ||
        Match(kx + 2, ky + 1, 'N') || Match(kx - 2, ky + 1, 'N'))
        return '1';

    if (Match(Kx + 1, Ky - 2, 'n') || Match(Kx - 1, Ky - 2, 'n') ||
        Match(Kx + 1, Ky + 2, 'n') || Match(Kx - 1, Ky + 2, 'n') ||
        Match(Kx + 2, Ky - 1, 'n') || Match(Kx - 2, Ky - 1, 'n') ||
        Match(Kx + 2, Ky + 1, 'n') || Match(Kx - 2, Ky + 1, 'n'))
        return '0';

    return '2';
}

char checkRrQq()
{
    int i = 1;
    while(Match(kx+i,ky, '.'))
        i++;
    if(IsValid(kx+i, ky) && (Board[kx+i][ky] == 'Q' || Board[kx+i][ky] == 'R') )
        return '1';
    
    i = 1;
   while(Match(kx-i,ky, '.'))
        i++;
    if(IsValid(kx-i, ky) && (Board[kx-i][ky] == 'Q' || Board[kx-i][ky] == 'R') )
        return '1'; 

    i = 1;
    while(Match(kx,ky+i, '.'))
        i++;
    if(IsValid(kx, ky+i) && (Board[kx][ky+i] == 'Q' || Board[kx][ky+i] == 'R') )
        return '1';
    
    i = 1;
    while(Match(kx,ky-i, '.'))
        i++;
    if(IsValid(kx, ky-i) && (Board[kx][ky-i] == 'Q' || Board[kx][ky-i] == 'R') )
        return '1';
    
    i = 1;
    while(Match(Kx+i,Ky, '.'))
        i++;
    if(IsValid(Kx+i, Ky) && (Board[Kx+i][Ky] == 'q' || Board[Kx+i][Ky] == 'r') )
        return '0';
    
    i = 1;
   while(Match(Kx-i,Ky, '.'))
        i++;
    if(IsValid(Kx-i, Ky) && (Board[Kx-i][Ky] == 'q' || Board[Kx-i][Ky] == 'r') )
        return '0'; 

    i = 1;
    while(Match(Kx,Ky+i, '.'))
        i++;
    if(IsValid(Kx, Ky+i) && (Board[Kx][Ky+i] == 'q' || Board[Kx][Ky+i] == 'r') )
        return '0';
    
    i = 1;
    while(Match(Kx,Ky-i, '.'))
        i++;
    if(IsValid(Kx, Ky-i) && (Board[Kx][Ky-i] == 'q' || Board[Kx][Ky-i] == 'r') )
        return '0';
    
    return '2';
}

char checkBbQq()
{
    int i = 1;
    while(Match(kx+i,ky+i, '.'))
        i++;
    if(IsValid(kx+i, ky+i) && (Board[kx+i][ky+i] == 'Q' || Board[kx+i][ky+i] == 'B') )
        return '1';
    
    i = 1;
   while(Match(kx-i,ky-i, '.'))
        i++;
    if(IsValid(kx-i, ky-i) && (Board[kx-i][ky-i] == 'Q' || Board[kx-i][ky-i] == 'B') )
        return '1'; 

    i = 1;
    while(Match(kx-i,ky+i, '.'))
        i++;
    if(IsValid(kx-i, ky+i) && (Board[kx-i][ky+i] == 'Q' || Board[kx-i][ky+i] == 'B') )
        return '1';
    
    i = 1;
    while(Match(kx+i,ky-i, '.'))
        i++;
    if(IsValid(kx+i, ky-i) && (Board[kx+i][ky-i] == 'Q' || Board[kx+i][ky-i] == 'B') )
        return '1';
    
    i = 1;
    while(Match(Kx+i,Ky+i, '.'))
        i++;
    if(IsValid(Kx+i, Ky+i) && (Board[Kx+i][Ky+i] == 'q' || Board[Kx+i][Ky+i] == 'b') )
        return '0';
    
    i = 1;
   while(Match(Kx-i,Ky-i, '.'))
        i++;
    if(IsValid(Kx-i, Ky-i) && (Board[Kx-i][Ky-i] == 'q' || Board[Kx-i][Ky-i] == 'b') )
        return '0'; 

    i = 1;
    while(Match(Kx-i,Ky+i, '.'))
        i++;
    if(IsValid(Kx-i, Ky+i) && (Board[Kx-i][Ky+i] == 'q' || Board[Kx-i][Ky+i] == 'b') )
        return '0';
    
    i = 1;
    while(Match(Kx+i,Ky-i, '.'))
        i++;
    if(IsValid(Kx+i, Ky-i) && (Board[Kx+i][Ky-i] == 'q' || Board[Kx+i][Ky-i] == 'b') )
        return '0';
    
    return '2';    
}

int main()
{
    bool terminal;   // flag for empty board
    int gameCnt = 0; // count the game number
    char check;      // flag for in check
    while (1)
    {
        gameCnt++;
        terminal = true;
        check = '2';
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                cin >> Board[i][j];
                if (Board[i][j] != '.')
                {
                    terminal = false;
                    if (Board[i][j] == 'k')
                    {
                        kx = i;
                        ky = j;
                    }
                    else if (Board[i][j] == 'K')
                    {
                        Kx = i;
                        Ky = j;
                    }
                }
            }
        }

        getchar();

        if (terminal)
            break;

        // Pawn and pawn
        check = checkPp();
        if (check != '2')
            goto OUTPUT;

        // Knight and knight
        check = checkKk();
        if (check != '2')
            goto OUTPUT;

        // Rook rook Queen queen
        check = checkRrQq();
        if(check != '2')
            goto OUTPUT;

        // Bishop bishop Queen queen
        check = checkBbQq();

    OUTPUT:
        cout << "Game #" << gameCnt << ": ";
        switch (check)
        {
        case '0':
            cout << "white";
            break;
        case '1':
            cout << "black";
            break;
        default:
            cout << "no";
        }
        cout << " king is in check." << endl;
    }

    return 0;
}
