#include <cstdio>
#include <algorithm>

using namespace std;

#define INF 0x3fffffff
#define maxN 5002
int len[maxN];
int dp[2][maxN];

int main()
{
    int T, K, N;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d %d", &K, &N);
        // reverse len[]
        for (int i = N; i > 0; i--)
        {
            scanf("%d", &len[i]);
            dp[0][i] = 0;
        }
        dp[0][0] = dp[1][0] = INF;

        for (int j = 1; j <= K + 8; j++)
        {
            for (int i = 1; i <= N; i++)
            {
                if (i >= 3 * j)
                {
                    dp[j % 2][i] = min(dp[j % 2][i - 1], dp[(j - 1) % 2][i - 2] + (len[i] - len[i - 1])*(len[i] - len[i - 1]));
                }
                else
                {
                    dp[j % 2][i] = dp[j % 2][i - 1];
                }
            }
        }
        
        printf("%d\n", dp[(K+8)%2][N]);
    }

    return 0;
}