#include <iostream>
#include <vector>

using namespace std;

#define MAX 5050

vector<int> Branch[MAX]; // adjacent list 
int Path[MAX]; // record the node in the path
int length; // record the length of the path

bool DFS(int u, int v, int pre)
{
    Path[length++] = u;
    if(u == v)
        return true;
    
    for(int i = 0; i < Branch[u].size(); i++)
    {
        if(Branch[u][i] == pre)  // make sure it doesn't go back
            continue;
        if( DFS(Branch[u][i],v,u) )
            return true;
    }
    
    length--;
    return false;
}

int main()
{
    int n, l;
    int s, t;
    while (cin >> n && n)
    {
        for(int i = 1; i <= n; i++)
            Branch[i].clear();

        for (int i = 0; i < n-1; i++)
        {
            cin >> s >> t;
            Branch[s].push_back(t);
            Branch[t].push_back(s);
        }

        cin >> l;
        for(int i = 0; i < l; i++)
        {
            cin >> s >> t;
            length = 0;
            DFS(s, t, -1);

            cout << "The fleas ";

            if(length % 2)
                cout << "meet at " << Path[length/2] <<"." << endl;
            else
            {
                int a = Path[ (length-1)/2 ];
                int b = Path[ (length+1)/2 ];
                if(a > b) swap(a, b);
                cout << "jump forever between " << a << " and " << b <<"." << endl;
            }
        } 
    }

    return 0;
}