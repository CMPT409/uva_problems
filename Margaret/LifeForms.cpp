#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>

// refer to suffix array ACM template:
// https://github.com/eecrazy/ACM/blob/master/%E6%A8%A1%E6%9D%BF/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/%E5%90%8E%E7%BC%80%E6%95%B0%E7%BB%84%E6%A8%A1%E6%9D%BF.cpp
//

// the length of input array
const int MAXN = 100 * 1001 + 5;

// used in SA()
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
void SA(int *r, int *sa, int n, int m)
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

// rank[i] = j  sa[j] = i
// height[i] means the LCP of suffix(i) and suffix(i-1)
int rank[MAXN], height[MAXN];
// function to build the height array
// r: input array
// sa: suffix array
// n: strlen(str)
void Height(int *r, int *sa, int n)
{
    int i, j, k;
    for (i = 1; i <= n; i++)
        rank[sa[i]] = i;
    for (i = k = 0; i < n; height[rank[i++]] = k)
        for (k ? k-- : 0, j = sa[rank[i] - 1]; r[i + k] == r[j + k]; k++)
            ;

    return;
}


int r[MAXN];  // long combined input string
int sa[MAXN]; // suffix array
char str[1005];
char idx[MAXN];  // array to record the responding sequence for every char
char visited[105]; // whether have visited the sequence

// when founded = false, use with binary search to find the
// longest common preffix appearing in the more than half sequences
//
// when founded = true, print all preffix satisfying requirement 
// n: strlen(r)
// stop: half of # of sequence + 1
// k: length of the assumed common preffix
bool judge(int k, int n, int stop, bool founded)
{
    int cnt = 0; // counter for sequences
    memset(visited, 0, sizeof(visited));

   if (!visited[(int)idx[sa[0]]])
   {
       visited[(int)idx[sa[0]]] = 1;
       cnt++;
   }

    for (int i = 1; i <= n; i++)
    {

        if (height[i] < k)
        {
            if (cnt >= stop && founded)
            {
                for (int j = sa[i - 1]; j < sa[i - 1] + k; j++)
                    printf("%c", (char)(r[j] - 1 + 'a'));

                printf("\n");
            }
            cnt = 0;
            memset(visited, 0, sizeof(visited));
        }

        if (!visited[(int)idx[sa[i]]])
        {
            visited[(int)idx[sa[i]]] = 1;
            cnt++;
        }

        if (cnt >= stop && !founded)
            return true;
    }

    if (cnt >= stop && founded)
    {
        for (int j = sa[n - 1]; j < sa[n - 1] + k; j++)
            printf("%c", (char)(r[j] - 1 + 'a'));

        printf("\n");
    }

    return false;
}


int main()
{
    bool blk = false;
    int n, len, L, R, mid, maxlen;
    
    while (scanf("%d", &n) == 1 && n)
    {

        // output a blank line between two test case
        if (blk){
            printf("\n");
        }
        else blk = true;
            

        if (n == 1)
        {
            scanf("%s", str);
            printf("%s\n", str);

            continue;
        }

        // combine input into a long string, insert separator between sequences
        // record the responding sequence for every char
        int sep = 27;
        len = 0;
        for (int j = 0; j < n; j++)
        {

            scanf("%s", str);
            for (int i = 0; i < strlen(str); i++)
            {
                idx[len] = (char)j;
                r[len++] = (int)(str[i] - 'a') + 1;
            }
            r[len++] = sep++;
        }
        r[len] = 0;

        // build suffix array and height array
        SA(r, sa, len + 1, sep);
        Height(r, sa, len);
        // binary search to find the LCP
        L = 0;
        R = len;
        maxlen = 0;
        while (L <= R)
        {
            mid = (L + R) >> 1;
            if (judge(mid, len, n / 2 + 1, false))  // find the length of common preffix
            {
                L = mid + 1;
                maxlen = std::max(mid,maxlen);
            }
            else
                R = mid - 1;
        }
        if (maxlen == 0)
            printf("?\n");
        else
        {
            judge(maxlen, len, n / 2 + 1, true); // print possible preffix
        }
    }
    return 0;
}
