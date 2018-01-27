#include <cstdio>

const int MAXN = 100005;
char str[MAXN];
int Len;

// algorithm of minimum representation.
int solve()
{
    if(Len == 1)
        return 0;
    
    int i = 0, j = 1;
    int k;
    while(i < Len && j < Len)
    {
        for(k = 0; k < Len; k++)
        {
            if(str[(i+k)%Len] != str[(j+k)%Len])
                break;
        }
        if(k == Len)
            break;
        
       if(str[(i+k)%Len] > str[(j+k)%Len])
            i = i+k+1;
        else j = j+k+1;

        if(i == j)
            j++;
    }

    return (i < j) ? i:j;
}

int main()
{
    int caseNum;
    scanf("%d", &caseNum);

    while(caseNum--)
    {
        scanf("%d %s", &Len, str);

        printf("%d\n", solve());
    }
    return 0;
}