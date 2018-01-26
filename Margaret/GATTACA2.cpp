#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
// refer to suffix array ACM template:
// https://github.com/eecrazy/ACM/blob/master/%E6%A8%A1%E6%9D%BF/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/%E5%90%8E%E7%BC%80%E6%95%B0%E7%BB%84%E6%A8%A1%E6%9D%BF.cpp
//

// the length of input array
const int MAXN = 1005;

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
char str[MAXN];

int hashInt(char c)
{
    switch (c)
    {
    case 'A': return 1;
    case 'C': return 2;
    case 'G': return 3;
    case 'T': return 4;
    }
    return 0;
}

char hashChar(int i)
{
   switch (i)
    {
    case 1: return 'A';
    case 2: return 'C';
    case 3: return 'G';
    case 4: return 'T';
    } 
    return 0;
}

bool judge(int k, int len, int* pos)
{
    for(int i = 1; i <= len; i++)
    {
        if(height[i] >= k)
        {
            *pos = sa[i-1];
            return true;
        }
            
    }
    return false;
}

int main()
{
    int caseNum, len, L, R, mid, maxlen, cnt;
    int *pos = (int*)malloc(sizeof(int));
    scanf("%d", &caseNum);
    while (caseNum--)
    {
        scanf("%s", str);
        len = strlen(str);
        for(int i = 0; i < len; i++)
        {
            r[i] = hashInt(str[i]);
        }
        r[len] = 0;
        
        SA(r,sa,len+1,5);
        Height(r,sa,len);

        L = 0;
        R = len;
        *pos = -1;
        maxlen = 0;
        while(L <= R)
        {
            mid = (L+R) >> 1;
            if(judge(mid,len,pos))
            {
                L = mid+1;
                maxlen = mid;
            }
            else R = mid - 1;
        }

        if(maxlen == 0)
        {
            printf("No repetitions found!\n");
        }
        else{
            for(int i = *pos; i < *pos+maxlen; i++)
                printf("%c", hashChar(r[i]));
            printf(" ");

            cnt = 1;
            for(int i = 1; i <= len; i++)
            {
                if(height[i] == maxlen)
                {
                    int j;
                    for(j = sa[i-1]; j < sa[i-1]+maxlen; j++)
                        if(r[ *pos+j-sa[i-1] ] != r[j])
                            break;
                    
                    if(j == sa[i-1] + maxlen)
                        cnt++;
                }
            }

            printf("%d\n", cnt);
        }
    }
    free(pos);
    return 0;
}