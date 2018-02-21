#include <algorithm>
#include <cstdio>

using namespace std;

#define INF 0x3fffffff
int M, N;
int grid[12][102], path[12][102];

int main()
{
    while(scanf("%d %d", &M, &N) != EOF)
    {
        for(int i = 0; i < M; ++i)
        {
            for(int j = 0; j < N; ++j)
            {
                scanf("%d", &grid[i][j]);
            }
        }

        int row, mingrid;
        for(int j = N-2; j >= 0; j--)
        {
            for(int i = 0; i < M; ++i)
            {
                row = i==0?M-1:i-1;
                mingrid = grid[row][j+1];
                
                if(mingrid > grid[i][j+1] || (mingrid == grid[i][j+1] && i < row) )
                {
                    row = i;
                    mingrid = grid[row][j+1];
                }


                if(mingrid > grid[(i+1)%M][j+1] || (mingrid == grid[(i+1)%M][j+1] && (i+1)%M < row) )
                {
                    row = (i+1)%M;
                    mingrid = grid[row][j+1];
                }
                grid[i][j] += mingrid;
                path[i][j] = row;
            }
        }

        int ans = grid[0][0];
        row = 0;
        for(int i = 1; i < M; ++i)
        {
            if(ans > grid[i][0])
            {
                row = i;
                ans = grid[i][0];
            }
        }
        
        printf("%d", row+1);
        for(int j = 0; j < N-1; ++j)
        {
            row = path[row][j];
            printf(" %d", row+1);
        }
        printf("\n%d\n", ans);
    }
    return 0;
}