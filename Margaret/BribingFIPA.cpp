#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <sstream>
#include <cstring>

using namespace std;
#define maxN 205
#define INF 0x3fffffff

int dp[maxN][maxN];
map<string, int> dcIdx;
vector<int> domain[maxN];
int price[maxN];
bool pre[maxN], vis[maxN];
int N, M;
int dcCnt;


inline void getIdx(string country){
    if(dcIdx.find(country) == dcIdx.end())
        dcIdx[country] = ++dcCnt; 
}

int readN()
{
    char c;
    int res = 0;
    for(c = getchar(); c < '0' || c > '9'; c = getchar())
    {
        if(c == '#') 
            return -1;
    }

    for( ;c >= '0' && c <= '9'; c = getchar(), res *= 10)
        res += (c-'0');
    
    return res/10;
}

int dfs(int u)
{
    vis[u] = true;
    int cnt = 1;
    for(int j = 0; j <= N; ++j)
        dp[u][j] = INF;
    
    dp[u][0] = 0;
    for(int i = 0; i < domain[u].size(); i++)
    {
        int v = domain[u][i];
        if(vis[v]) continue;
        cnt += dfs(v);
        
        for(int j = N; j >= 0; j--)
            for(int k = 1; k <= j; k++)
            {
                dp[u][j] = min(dp[u][j], dp[u][j-k]+dp[v][k]); 
            }
    }

    dp[u][cnt] = min(dp[u][cnt], price[u]);
    
    return cnt;
}

int main(){
    char dcName[105], subName[105];
    int diaCnt; 
    while (1)
    {
        N = readN();
        if(N < 0) break;
        scanf("%d", &M);

        for(int i = 0; i <= N; ++i)
        {
            domain[i].clear();
            pre[i] = false;
            vis[i] = false;
        }
        dcCnt = 0;
        dcIdx.clear();

        for (int i = 0; i < N; ++i)
        {
            scanf("%s %d", dcName, &diaCnt);

            getIdx(dcName);
            price[dcIdx[dcName]] = diaCnt;
            char str[1000];
            gets(str);
            stringstream ss(str);
            while (ss >> subName)
            {
                getIdx(subName);
                domain[dcIdx[dcName] ].push_back(dcIdx[subName]);
                pre[dcIdx[subName] ] = true;
            }
        }

        price[0] = INF;
        for(int i = 1; i <= N; i++)
        {
            if(!pre[i]) domain[0].push_back(i); 
        }

        dfs(0);
        int ans = INF;
        for(int i = M; i <= N; ++i)
            ans = min(ans, dp[0][i]);
        
        printf("%d\n", ans);
        
    }

    return 0;
}