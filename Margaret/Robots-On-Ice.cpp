#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdlib>
using namespace std;

#define MAXL 8+2
char grid[MAXL][MAXL];
int m, n;
int r1, c1, r2, c2, r3, c3;
int cp1, cp2, cp3, cp4;
int ans;

// check whether the grid is inside of the range and whether it's unvisited
inline bool Reachable(int x, int y)
{
	return x>= 0 && x < m && y >= 0 && y < n && grid[x][y] == -1;
}

// manhattan distance, i.e, the minimal distance to check point
inline int manhattan(int x, int y, int mark)
{
	switch(mark){
		case 1:
			return abs(x - r1) + abs(y-c1); 
		case 2:
			return abs(x - r2) + abs(y-c2); 
		case 3:
			return abs(x - r3) + abs(y-c3); 
		case 4:
			return abs(x)+abs(y-1);
		default:
			return -1;
	}
}

// whether the current point cut the unvisited points into two separate parts
int neighbour [9];
bool IsConnected(int x, int y)
{
	neighbour[0] = Reachable(x-1, y-1);
	neighbour[1] = Reachable(x-1, y);
	neighbour[2] = Reachable(x-1,y+1);
	neighbour[3] = Reachable(x,y+1);
	neighbour[4] = Reachable(x+1, y+1);
	neighbour[5] = Reachable(x+1,y);
	neighbour[6] = Reachable(x+1, y-1);
	neighbour[7] = Reachable(x, y-1);
	neighbour[8] = neighbour[0];

	int dispatch = 0;
	for(int i = 0; i < 8; ++i)
		if(neighbour[i] != neighbour[i+1])
			dispatch++;

	return dispatch < 4;
}

// do dfs and cut-off
void dfs(int x, int y)
{
	if(grid[x][y] < cp1)
	{
		if(manhattan(x, y, 1) > cp1-grid[x][y] || manhattan(x, y, 1) == 0)
		{
			grid[x][y] = -1;
			return;
		}
	}
	else if(grid[x][y] == cp1)
	{
		if(x != r1 || y != c1)
		{
			grid[x][y] = -1;
			return;
		}
	}
	else if(grid[x][y] < cp2)
	{
		if(manhattan(x, y, 2) > cp2-grid[x][y] || manhattan(x, y, 2) == 0)
		{
			grid[x][y] = -1;
			return;
		}
	}
	else if(grid[x][y] == cp2)
	{
		if(x != r2 || y != c2)
		{
			grid[x][y] = -1;
			return;
		}
	}
	else if(grid[x][y] < cp3)
	{
		if(manhattan(x, y, 3) > cp3-grid[x][y] || manhattan(x, y, 3) == 0)
		{
			grid[x][y] = -1;
			return;
		}
	}
	else if(grid[x][y] == cp3)
	{
		if(x != r3 || y != c3)
		{
			grid[x][y] = -1;
			return;
		}
	}
	else if(grid[x][y] < cp4)
	{
		if(manhattan(x, y, 4) > cp3-grid[0][1] || manhattan(x, y, 4) == 0)
		{
			grid[x][y] = -1;
			return;
		}
	}
	else if(grid[x][y] == cp4)
	{
		if(x == 0 && y == 1)
			ans++;

		grid[x][y] = -1;
		return;
	}

	if(x == r1 && y == c1)
	{
		if(grid[x][y] != cp1)
		{
			grid[x][y] = -1;
			return;
		}
	}
	else if(x == r2 && y == c2)
	{
		if(grid[x][y] != cp2)
		{
			grid[x][y] = -1;
			return;
		}
	}
	else if(x == r3 && y == c3)
	{
		if(grid[x][y] != cp3)
		{
			grid[x][y] = -1;
			return;
		}
	}
	else if(x == 0 && y == 1)
	{
		if(grid[x][y] == cp4)
			ans++;

		grid[x][y] = -1;
		return;
	}

	if(!IsConnected(x,y))
	{
		grid[x][y] = -1;
		return;
	}

	if(Reachable(x-1, y))
	{
		grid[x-1][y] = grid[x][y]+1;
		dfs(x-1, y);
	}

	if(Reachable(x, y-1))
	{
		grid[x][y-1] = grid[x][y]+1;
		dfs(x, y-1);
	}

	if(Reachable(x+1, y))
	{
		grid[x+1][y] = grid[x][y]+1;
		dfs(x+1, y);
	}

	if(Reachable(x, y+1))
	{
		grid[x][y+1] = grid[x][y]+1;
		dfs(x, y+1);
	}

	grid[x][y] = -1;
}

void solve()
{
	memset(grid, -1, sizeof(grid));
	cp1 = m*n/4;
	cp2 = m*n/2;
	cp3 = m*n*3/4;
	cp4 = m*n;
	ans = 0;
	
	grid[0][0] = 1;
	grid[1][0] = 2;
	dfs(1,0);
}

int main()
{
	int caseCnt = 1;
	while(cin >> m >> n)
	{
		if(m == 0 && n == 0)
			break;

		cin >> r1 >> c1 >> r2 >> c2 >> r3 >> c3;
		solve();
		cout << "Case "<<caseCnt<<": " << ans << endl;
		caseCnt++;
	}

	return 0;
}