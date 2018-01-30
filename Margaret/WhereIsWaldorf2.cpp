#include <cstdio>
#include <cstring>
#include <ctype.h>
#include <algorithm>

const int SIZE = 52;
const int MAXN = SIZE*SIZE*SIZE*4;
char str[SIZE][SIZE];
int row, col;
char word[SIZE], grid[MAXN];
int grid_ptr;
int sa[MAXN], idx[MAXN];

int wa[MAXN], wb[MAXN], wv[MAXN], ws[MAXN];
inline bool cmp(int *r, int a, int b, int len)
{
    return r[a] == r[b] && r[a + len] == r[b + len];
}

// function to build the suffix array
// r: input array
// sa: suffix array
// n: strlen(r)+1
// m: max(r[i])+1
void SA(char *r, int *sa, int n, int m)
{

    int i, j, p, *x = wa, *y = wb, *t;

    for (i = 0; i < m; i++)
        ws[i] = 0;
    for (i = 0; i < n; i++)
        ws[x[i] = r[i]]++;
    for (i = 1; i < m; i++)
        ws[i] += ws[i - 1];
    for (i = n - 1; i >= 0; i--)
        sa[--ws[x[i]]] = i;

    for (j = p = 1; p < n; j <<= 1, m = p)
    {

        for (p = 0, i = n - j; i < n; i++)
            y[p++] = i;
        for (i = 0; i < n; i++)
        {
            if (sa[i] >= j)
                y[p++] = sa[i] - j;
        }

        for (i = 0; i < m; i++)
            ws[i] = 0;
        for (i = 0; i < n; i++)
            ws[wv[i] = x[y[i]]]++;
        for (i = 1; i < m; i++)
            ws[i] += ws[i - 1];
        for (i = n - 1; i >= 0; i--)
            sa[--ws[wv[i]]] = y[i];
        for (t = x, x = y, y = t, x[sa[0]] = 0, p = i = 1; i < n; i++)
            x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
    }
}





inline bool InRange(int x, int y)
{
    return (x >= 0) && (x < row) && (y >= 0) && (y < col);
}


void build_grid(int x, int y)
{
    int nx, ny, cnt;
    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            if(i == 0 && j == 0)
                continue;
            for(cnt = 0; ;cnt++){
                nx = x + cnt*i;
                ny = y + cnt*j;
                
                if(!InRange(nx, ny))
                    break;

                idx[grid_ptr] = nx*col+ny;  // record the position of the character
                grid[grid_ptr++] = str[nx][ny];
            }
            grid[grid_ptr++] = (char)27;
        }
    }
}
int match(int pos)
{
    for(int i = 0; i < strlen(word); i++)
    {
        if(grid[pos+i] > word[i])
            return 1;
        else if(grid[pos+i] < word[i])
            return -1;
    }
    return 0;
}
void solve()
{
    int L, R, mid;
    for(L = 0, R = grid_ptr, mid = (L+R) >> 1; L <= R;mid = (L+R) >> 1)
    {
        if(match(sa[mid]) == 1)
            R = mid-1;
        else if(match(sa[mid]) == -1)
            L = mid+1;
        else{
            break;
        }
    }
    int ans = MAXN;
    for(int i = 0; mid - i >= L && match(sa[mid-i]) == 0; i++)
        ans = std::min(ans, idx[sa[mid-i]]);
    for(int i = 0; mid + i <= R && match(sa[mid+i]) == 0; i++)
        ans = std::min(ans, idx[sa[mid+i]]);

    printf("%d %d\n", ans/col+1, ans%col+1);
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
                str[i][j] = (char)(tolower(str[i][j]) - 'a' + 1);
            }
        }

        grid_ptr = 0;
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < col; j++)
            {
                build_grid(i,j);
            }
        }
       grid[grid_ptr] = 0;
        // test
//        for(int i = 0; i < grid_ptr-1; i++)
//            printf("%c", grid[i]-1+'a');
//        printf("\n");
//        return 0;

        SA(grid,sa, grid_ptr+1, 28);

        scanf("%d", &wordNum);
        while (wordNum--)
        {
            scanf("%s", word);
            for (int i = 0; i < strlen(word); i++)
                word[i] = (char)(tolower(word[i]) - 'a' + 1);

            solve();
        }
    }
    return 0;
}