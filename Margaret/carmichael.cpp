#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>

using namespace std;

#define MAXN 65002
char nums [MAXN];
int primes[MAXN/2];

// find out all prime numbers among 2 to 65000
// store them in memory
void prime_table()
{
    memset(nums,0,sizeof(nums));
    int cnt = 0;
    for(int i = 2; i < MAXN; ++i)
    {
        if(!nums[i])
            primes[cnt++] = i;
        for(int j = 0; j < cnt && primes[j]*i<MAXN; ++j)
            nums[primes[j]*i] = 1;
    }
}

// must use "long long" type
// a can be very large
long long fermat(long long a, int pow, int n)
{
    long long res = 1;
    while(pow)
    {
        if(pow % 2)
            res = (res*a) %n;

        a = (a*a)%n;
        pow >>= 1; 
    }
    return res;
}

int main()
{
    prime_table();

    int n, i;
    while(cin >> n && n != 0)
    {
        if(nums[n])
        {
            for(i = 2; i < n; ++i)
                if(fermat(i, n, n) != i)
                    break;
            if(i == n){
                printf("The number %d is a Carmichael number.\n", n);
                continue;
            }
        }

        printf("%d is normal.\n", n);
    }
    return 0;
}