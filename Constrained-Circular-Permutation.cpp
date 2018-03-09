#include <iostream>
#include <vector>

using namespace std;

typedef struct{
	short num[15];
} Cface;

int size, maxsum;
int num_cnt, face_cnt;
vector<Cface> ans;

bool test(Cface face, int len)
{
	for(int i = 0; i < len; ++i)
		if( face.num[i]+face.num[(i+1)%len]+face.num[(i+2)%len] > maxsum)
			return false;

	return true;
}

void permutation()
{
	if(num_cnt == size)
		return;

	// refine
	vector<Cface> tmp; 
	for(int i = 0; i < face_cnt; ++i)
		if(test(ans[i], num_cnt))
			tmp.push_back(ans[i]);

	face_cnt = tmp.size();
	if(face_cnt == 0)
		return;

	// insert next number
	ans.clear();
	for(int i = 0; i < face_cnt; i++)
	{
		for(int j = i*num_cnt; j < (i+1)*num_cnt; j++)
		{
			ans.push_back(tmp[i]);
			
			for(int k = 0; k < num_cnt+1; k++)
			{
				if(k + j == (i+1)*num_cnt)
					ans[j].num[k] = num_cnt+1;
				else if(k + j > (i+1)*num_cnt)
					ans[j].num[k] = tmp[i].num[k-1];
			}
		}
	}
	
	face_cnt *= num_cnt;
	num_cnt++;
	permutation();
}

void solve(int idx)
{
	int valid_cnt = 0;

	if(size >= 3)
	{
		Cface c;
		c.num[0] = 1;
		c.num[1] = 2;
		c.num[2] = 3;
		ans.clear();
		ans.push_back(c);
		num_cnt = 3;
		face_cnt = 1;
		permutation();

		for(int i = 0; i < face_cnt; ++i)
			if(test(ans[i], num_cnt))
				valid_cnt++;
	}

	if(idx != 0)
		cout << endl;
	cout << "Permutation size:    " << size << endl;
	cout << "Maximum triplet sum: " << maxsum << endl;
	cout << "Valid permutations:  " << valid_cnt << endl;
}

int main()
{
	int caseNum;
	cin >> caseNum;
	
	int i;
	for(int i = 0; i < caseNum; ++i)
	{
		cin >> size >> maxsum;
		solve(i);
	}

	return 0;
}