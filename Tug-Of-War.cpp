#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace std;
// dp[n][w] = max(dp[n-1][w], dp[n-1][w-wi]+1)
int n, sumweight;
int weight[105];
#define MAXW 450*100/2+5

long long dp[MAXW];

void solve(int idx)
{
	memset(dp, 0, sizeof(dp));
	dp[0] = 1LL;

	int halfweight = sumweight>>1;

	for(int i = 1; i <= n; ++i)
		for(int j = halfweight; j >= weight[i]; --j)
			dp[j] |= (dp[j-weight[i]]<<1);  // bitmask for the exact weight sum

	int res, halfn = n / 2;
	if(n & 1)
		for(res = halfweight; res >= 0 && !(dp[res]&(1LL<<halfn)) && !(dp[res]&(1LL<<(halfn+1) )); --res)
			;
	else for(res = halfweight; res >= 0 && !(dp[res]&(1LL<<halfn)); --res)
		;

	cout << res << " " << sumweight-res << endl;
	if(idx)
		cout << endl;
}

int main()
{
	int caseNum;
	cin >> caseNum;
	while(caseNum--)
	{
		cin >> n;
		sumweight = 0;
		for(int i = 1; i <= n; ++i)
		{
			cin >> weight[i];
			sumweight += weight[i];
		}
		solve(caseNum);
	}
	return 0;
}