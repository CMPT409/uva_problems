#include <cstdio>
#include <cstring>
#include <ctype.h>

const int MAXN = 55;
char str[MAXN][MAXN];
int row, col;
char word[MAXN];
int dir[3] = {-1, 0, 1};

bool inRange(int x, int y)
{
    return (x >= 0) && (x < row) && (y >= 0) && (y < col);
}

void solve()
{
    int step, nexti, nextj;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            // scan the grid until find the first letter in the word
            if (str[i][j] == word[0])
            {
                // check the rest letters
                for (int v = 0; v < 3; v++)
                {
                    for (int h = 0; h < 3; h++)
                    {
                        if (v == 1 && h == 1)
                            continue;

                        for (step = 1; step < strlen(word); step++)
                        {
                            nexti = i + dir[v] * step;
                            nextj = j + dir[h] * step;
                            if (!inRange(nexti, nextj) || str[nexti][nextj] != word[step])
                                break;
                        }
                        if (step == strlen(word))
                        {
                            printf("%d %d\n", i + 1, j + 1);
                            return;
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    int caseNum, wordNum;
    bool blank = false;
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        // print blank line between test case
         if (blank)
            printf("\n");
        else
            blank = true;

        scanf("%d %d", &row, &col);
        for (int i = 0; i < row; i++)
        {
            scanf("%s", str[i]);
            for (int j = 0; j < col; j++)
            {
                str[i][j] = tolower(str[i][j]);
            }
        }

        scanf("%d", &wordNum);
 
        while (wordNum--)
        {
            scanf("%s", word);
            for (int i = 0; i < strlen(word); i++)
                word[i] = tolower(word[i]);

            solve();
        }
    }
    return 0;
}