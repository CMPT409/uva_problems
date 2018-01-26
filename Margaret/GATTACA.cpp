#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// refer to stanford's ACM notebook
struct SuffixArray
{
    const int L;
    string s;
    vector<vector<int> > P;
    vector<pair<pair<int, int>, int> > M;

    SuffixArray(const string &s) : L(s.length()), s(s), P(1, vector<int>(L, 0)), M(L)
    {

        for (int i = 0; i < L; i++)
            P[0][i] = int(s[i]);
        for (int skip = 1, level = 1; skip < L; skip *= 2, level++)
        {
            P.push_back(vector<int>(L, 0));
            for (int i = 0; i < L; i++)
                M[i] = make_pair(make_pair(P[level - 1][i], i + skip < L ? P[level - 1][i + skip] : -1000), i);
            sort(M.begin(), M.end());
            for (int i = 0; i < L; i++)
                P[level][M[i].second] = (i > 0 && M[i].first == M[i - 1].first) ? P[level][M[i - 1].second] : i;
        }
    }

    vector<int> GetSuffixArray() { return P.back(); }

    // returns the length of the longest common prefix of s[i...L-1] and s[j...L-1]
    int LongestCommonPrefix(int i, int j)
    {
        int len = 0;
        if (i == j)
            return L - i;
        for (int k = P.size() - 1; k >= 0 && i < L && j < L; k--)
        {
            if (P[k][i] == P[k][j])
            {
                i += 1 << k;
                j += 1 << k;
                len += 1 << k;
            }
        }
        return len;
    }
};

void solve ()
{
        string S;
        cin >> S;
        SuffixArray sa(S);

        int cnt = 0, len, templen;
        int longest = -1, pos = -1, count = 0;
        for (int i = 0; i < S.length(); i++)
        {
            len = 0;
            for (int j = i + 1; j < S.length(); j++)
            {
                templen = sa.LongestCommonPrefix(i, j);

                if (templen >= len)
                {

                    if (len == templen)
                        cnt++;
                    else
                        cnt = 2;
                    len = templen;
                }
            }

            if (longest < len || (longest == len && S.substr(pos, len) > S.substr(i, len)))
            {
                longest = len;
                pos = i;
                count = cnt;
            }
        }
        if (longest == 0)
        {
            cout << "No repetitions found!" << endl;
        }
        else
        {
            cout << S.substr(pos, longest) << " " << count << endl;
        }
}

int main()
{
    int T;
    cin >> T;

    for (int k = 0; k < T; k++)
    {
        solve();
    }

    return 0;
}