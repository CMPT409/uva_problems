#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

// the template of big number
// reference: http://www.cnblogs.com/HarryGuo2012/p/4524041.html
#define MAX_L 100+5
class bign
{
public:
    int len, s[MAX_L];
//constructor
    bign();
    bign(const char*);
    bign(int);
    bool sign;//sign 1 positive 0 negative
    
    string toStr() const;
    friend ostream& operator<<(ostream &,bign &);

//copy 
    bign operator=(const char*);
    bign operator=(int);
    bign operator=(const string);
//comparison
    bool operator>(const bign &) const;
    bool operator>=(const bign &) const;
    bool operator<(const bign &) const;
    bool operator<=(const bign &) const;
    bool operator==(const bign &) const;
    bool operator!=(const bign &) const;
//add
    bign operator+(const bign &) const;
    bign operator++();
    bign operator++(int);
    bign operator+=(const bign&);
    bign operator-(const bign &) const;

    void clean();
    ~bign();
};

bign::bign()
{
    memset(s, 0, sizeof(s));
    len = 1;
    sign = 1;
}

bign::bign(const char *num)
{
    *this = num;
}

bign::bign(int num)
{
    *this = num;
}

string bign::toStr() const
{
    string res;
    res = "";
    for (int i = 0; i < len; i++)
        res = (char)(s[i] + '0') + res;
    if (res == "")
        res = "0";
    if (!sign&&res != "0")
        res = "-" + res;
    return res;
}

ostream &operator<<(ostream &out, bign &num)
{
    out<<num.toStr();
    return out;
}

bign bign::operator=(const char *num)
{
    memset(s, 0, sizeof(s));
    char a[MAX_L] = "";
    if (num[0] != '-')
        strcpy(a, num);
    else
        for (int i = 1; i < strlen(num); i++)
            a[i - 1] = num[i];
    sign = !(num[0] == '-');
    len = strlen(a);
    for (int i = 0; i < strlen(a); i++)
        s[i] = a[len - i - 1] - 48;
    return *this;
}

bign bign::operator=(int num)
{
    char temp[MAX_L];
    sprintf(temp, "%d", num);
    *this = temp;
    return *this;
}

bign bign::operator=(const string num)
{
    const char *tmp;
    tmp = num.c_str();
    *this = tmp;
    return *this;
}

bool bign::operator<(const bign &num) const
{
    if (sign^num.sign)
        return num.sign;
    if (len != num.len)
        return len < num.len;
    for (int i = len - 1; i >= 0; i--)
        if (s[i] != num.s[i])
            return sign ? (s[i] < num.s[i]) : (!(s[i] < num.s[i]));
    return !sign;
}

bool bign::operator>(const bign&num)const
{
    return num < *this;
}

bool bign::operator<=(const bign&num)const
{
    return !(*this>num);
}

bool bign::operator>=(const bign&num)const
{
    return !(*this<num);
}

bool bign::operator!=(const bign&num)const
{
    return *this > num || *this < num;
}

bool bign::operator==(const bign&num)const
{
    return !(num != *this);
}

bign bign::operator+(const bign &num) const
{
    if (sign^num.sign)
    {
        bign tmp = sign ? num : *this;
        tmp.sign = 1;
        return sign ? *this - tmp : num - tmp;
    }
    bign result;
    result.len = 0;
    int temp = 0;
    for (int i = 0; temp || i < (max(len, num.len)); i++)
    {
        int t = s[i] + num.s[i] + temp;
        result.s[result.len++] = t % 10;
        temp = t / 10;
    }
    result.sign = sign;
    return result;
}

bign bign::operator++()
{
    *this = *this + 1;
    return *this;
}

bign bign::operator++(int)
{
    bign old = *this;
    ++(*this);
    return old;
}

bign bign::operator+=(const bign &num)
{
    *this = *this + num;
    return *this;
}

bign bign::operator-(const bign &num) const
{
    bign b=num,a=*this;
    if (!num.sign && !sign)
    {
        b.sign=1;
        a.sign=1;
        return b-a;
    }
    if (!b.sign)
    {
        b.sign=1;
        return a+b;
    }
    if (!a.sign)
    {
        a.sign=1;
        b=bign(0)-(a+b);
        return b;
    }
    if (a<b)
    {
        bign c=(b-a);
        c.sign=false;
        return c;
    }
    bign result;
    result.len = 0;
    for (int i = 0, g = 0; i < a.len; i++)
    {
        int x = a.s[i] - g;
        if (i < b.len) x -= b.s[i];
        if (x >= 0) g = 0;
        else
        {
            g = 1;
            x += 10;
        }
        result.s[result.len++] = x;
    }
    result.clean();
    return result;
}

void bign::clean()
{
    if (len == 0) len++;
    while (len > 1 && s[len - 1] == '\0')
        len--;
}

bign::~bign()
{
}

#define maxL 10000+5
#define maxN 100+5
char X[maxL], Z[maxN]; 
bign dp[maxN][maxL];
// dp[i][0] = 0     dp[0][j] = 1
// dp[i][j] = dp[i][j-1]  x[j] != z[i]
// dp[i][j] = dp[i][j-1]+dp[i-1][j-1] x[j] == z[i]

int main()
{
    int N; 
    scanf("%d", &N);
    while(N--)
    {
        scanf("%s", X);
        scanf("%s", Z);
        int len1 = strlen(X);
        int len2 = strlen(Z);

        for(int i = 0; i <= len2; ++i)
            dp[i][0] = 0;
        
        for(int j = 0; j <= len1; ++j)
            dp[0][j] = 1;

        for(int i = 1; i <= len2; ++i)
        {
           for(int j = 1; j <= len1; ++j)
            {
               dp[i][j] = dp[i][j-1];
               if(X[j-1] == Z[i-1])
                    dp[i][j] += dp[i-1][j-1];
            } 
        }
        cout << dp[len2][len1]<< endl;
    }
    return 0;
}