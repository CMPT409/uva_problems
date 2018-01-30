#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iomanip>
using namespace std;

struct SuffixArray
{
	const int L;
	string s;
	vector<vector<int>> P;
	vector<pair<pair<int, int>, int>> M;
    vector<int> array;
    vector<int> rank;
    vector<int> height;
    vector<int> label;
    vector<int> arrayLabel;

	SuffixArray(const string &s) : L(s.length()), s(s), P(1, vector<int>(L, 0)), M(L),
        array(vector<int>(L, 0)), height(vector<int>(L, 0)), label(vector<int>(L, 0)), arrayLabel(vector<int>(L, 0))
	{
		for(int i = 0; i < L; i++) P[0][i] = int(s[i]);
		for(int skip = 1, level = 1; skip < L; skip *= 2, level++) {
			P.push_back(vector<int>(L, 0));
			for(int i = 0; i < L; i++) {
				M[i] = make_pair(make_pair(P[level-1][i], i+skip < L ? P[level-1][i+skip] : 1000), i);
			}
			sort(M.begin(), M.end());
			for(int i = 0; i < L; i++) {
				P[level][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ? P[level][M[i-1].second] : i;
			}
		}

        rank = P.back();
        for (size_t i = 0; i < L; i++) {
            array[rank[i]] = i;
        }

        int h = 0;
        for (size_t i = 0; i < L; i++) {
            if (rank[i] > 0) {
                int j = array[rank[i] - 1];
                while (s[i+h] == s[j+h]) {
                    h++;
                }
                height[rank[i]] = h;
                if (h > 0) {
                    h -= 1;
                }
            }
        }
    }

	int longestCommonPrefix(int i, int j)
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

    friend ostream& operator << (ostream& os, const SuffixArray& sa);
};

ostream& operator << (ostream& os, const SuffixArray& sa)
{
    os << "String: " << sa.s << endl;
    os << "SuffixArray: \t";
    for (size_t i = 0; i < sa.L; i++) {
        cout << setw(2) << sa.array[i] << ' ';
    }
    cout << endl;

    os << "rank: \t\t";
    for (size_t i = 0; i < sa.L; i++) {
        cout << setw(2) << sa.rank[i] << ' ';
    }
    cout << endl;
}


int main(int argc, char const *argv[]) {
    int caseNum;
    cin >> caseNum;
    for (size_t caseno = 0; caseno < caseNum; caseno++) {
        int L;
        cin >> L;
        string S;
        cin >> S;
        S += S;
        SuffixArray sa(S);
        // cout << sa;
        for (int i = 0; i < sa.L; i++) {
            if (sa.array[i] < L) {
                cout << sa.array[i] << endl;
                break;
            }
        }
    }

    return 0;
}
