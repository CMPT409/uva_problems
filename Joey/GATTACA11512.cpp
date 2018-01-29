#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct SuffixArray
{
	const int L;
	string s;
	vector<vector<int>> P;
	vector<pair<pair<int, int>, int>> M;

	SuffixArray(const string &s) : L(s.length()), s(s), P(1, vector<int>(L, 0)), M(L)
	{
		for(int i = 0; i < L; i++) P[0][i] = int(s[i]);
		for(int skip = 1, level = 1; skip < L; skip *= 2, level++) {
			P.push_back(vector<int>(L, 0));
			for(int i = 0; i < L; i++) {
				M[i] = make_pair(make_pair(P[level-1][i], i+skip < L ? P[level-1][i+skip] : -1000), i);
			}
			sort(M.begin(), M.end());
			for(int i = 0; i < L; i++) {
				P[level][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ? P[level][M[i-1].second] : i;
			}
		}
	}

	vector<int> getSuffixArray()
	{
		return P.back();
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
};

int main(int argc, char const *argv[])
{
	int caseNum;
	cin >> caseNum;
	for (int caseno = 0; caseno < caseNum; caseno ++)
	{
		string line;
		cin >> line;
		SuffixArray suffix(line);
		int maxLen = -1, maxCount = 0, pos = -1;

		for (int i = 0; i < line.length(); ++i)
		{
			int localMaxLen = 0, localMaxCount = 0;
			for (int j = i + 1; j < line.length(); ++j)
			{
				int len = suffix.longestCommonPrefix(i, j);
				if (len >= localMaxLen)
				{
					if (len > localMaxLen)
						localMaxCount = 2;
					else
						localMaxCount++;
					localMaxLen = len;
				}
			}
			if (localMaxLen > maxLen || localMaxLen == maxLen &&
				 line.substr(i, localMaxLen) < line.substr(pos, maxLen)) {
				maxLen = localMaxLen;
				maxCount = localMaxCount;
				pos = i;
			}
		}
		if (maxLen == 0) {
			cout << "No repetitions found!" << endl;
		}
		else{
			cout << line.substr(pos, maxLen) << ' ' << maxCount << endl;
		}
	}
	return 0;
}
