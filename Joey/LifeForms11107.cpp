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
				M[i] = make_pair(make_pair(P[level-1][i], i+skip < L ? P[level-1][i+skip] : -1000), i);
			}
			sort(M.begin(), M.end());
			for(int i = 0; i < L; i++) {
				P[level][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ? P[level][M[i-1].second] : i;
			}
		}

        int del;
        for (int i = L - 1; i >= 0; i--) {
            if(int(s[i]) < 0){
                del = int(s[i]);
            }
            label[i] = del;
        }

        rank = P.back();
        for (size_t i = 0; i < L; i++) {
            array[rank[i]] = i;
            arrayLabel[rank[i]] = label[i];
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

    os << "height: \t";
    for (size_t i = 0; i < sa.L; i++) {
        cout << setw(2) << sa.height[i] << ' ';
    }
    cout << endl;

    os << "label: \t\t";
    for (size_t i = 0; i < sa.L; i++) {
        cout << setw(2) << sa.label[i] << ' ';
    }
    cout << endl;

    os << "arrayLabel: \t";
    for (size_t i = 0; i < sa.L; i++) {
        cout << setw(2) << sa.arrayLabel[i] << ' ';
    }
    cout << endl;
}

int main(int argc, char const *argv[]) {
    int caseNum;
    cin >> caseNum;
    while (caseNum != 0) {
        if (caseNum == 1) {
            string line;
            cin >> line;
            cout << line << endl << endl;
            continue;
        }

        string S;
        char del = -1;
        for (size_t caseno = 0; caseno < caseNum; caseno++) {
            string line;
            cin >> line;
            S += line + del;
            del--;
        }
        SuffixArray sa(S);
        // cout << sa << endl;

        int L = 0, R = 0;
        int half = (caseNum) / 2 + 1;
        int minHeightInRange = sa.L;
        int maxHeight = -1;
        int maxPos[sa.L];
        int maxCnt = 0;
        int labelCnt = 0;
        unordered_map<int, int> labelInRange;
        while (R < sa.L){
            if (!labelInRange[sa.arrayLabel[R]]) {
                labelInRange[sa.arrayLabel[R]] = 1;
                labelCnt++;
            }
            else{
                labelInRange[sa.arrayLabel[R]] += 1;
            }
            if (labelCnt < half) {
                R++;
            }
            else{
                break;
            }
        }
        while (labelInRange[sa.arrayLabel[L]] > 1) {
            labelInRange[sa.arrayLabel[L++]] -= 1;
        }
        while (R < sa.L) {
            minHeightInRange = sa.longestCommonPrefix(sa.array[L], sa.array[R]);
            if (maxHeight < minHeightInRange && minHeightInRange != 0) {
                maxCnt = 0;
                maxPos[maxCnt++] = sa.array[L];
                maxHeight = minHeightInRange;
            }
            else if (maxHeight == minHeightInRange && minHeightInRange != 0 && maxPos[maxCnt-1] != sa.array[L]) {
                maxPos[maxCnt++] = sa.array[L];
            }
            while (L < sa.L) {
                labelInRange[sa.arrayLabel[L++]] -= 1;
                if (labelInRange[sa.arrayLabel[L-1]] == 0) {
                    break;
                }
            }
            while (++R < sa.L) {
                labelInRange[sa.arrayLabel[R]] += 1;
                if (labelInRange[sa.arrayLabel[R]] == 1) {
                    break;
                }
            }
            while (labelInRange[sa.arrayLabel[L]] > 1) {
                labelInRange[sa.arrayLabel[L++]] -= 1;
            }
        }
        if (maxCnt == 0) {
            cout << "?" << endl;
        }
        else{
            for (int i = 0; i < maxCnt; i++) {
                if (i != 0 && sa.s.substr(maxPos[i], maxHeight) == sa.s.substr(maxPos[i-1], maxHeight)) {
                    continue;
                }
                cout << sa.s.substr(maxPos[i], maxHeight) <<endl;
            }
        }
        cin >> caseNum;
        if (caseNum == 0) {
            break;
        }
        cout << endl;
    }

    return 0;
}
