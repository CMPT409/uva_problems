#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

#define MAX 1000
#define INF 0x7fffffff


vector<vector<int> > relation; // adjacent list (edge between co-authors)
map<string, int> person;      // the index for people
vector<int> erdos;  // erdos number for people

int coauthor[MAX]; // record index of authors of one paper

vector<int> vectorOfInt; // used to add entry in the adjacent list

int main()
{
    int scenario;  // number of scenario
    int scenIndex; // scenario index
    int P, N;
    int num;   // number of authors of one paper
    int index; // number of people
    string line, name;

    cin >> scenario;

    for (scenIndex = 1; scenIndex <= scenario; scenIndex++)
    {
        cin >> P >> N;
        getchar();
        index = 0;
        person.clear();
        relation.clear();

        // input for paper information
        for (int i = 0; i < P; i++)
        {
            getline(cin, line);

            num = 0;

            for (int j = 0, tmp = 0; line[j] != '\0'; j++)
            {
                if (line[j] == '.' && (line[j + 1] == ',' || line[j + 1] == ':'))
                {
                    name = line.substr(tmp, j - tmp + 1);

                    if (person.find(name) == person.end())
                    {
                        person[name] = index++;
                        relation.push_back(vectorOfInt);
                    }

                    coauthor[num++] = person[name];

                    tmp = j + 3;
                }
            }

            // update adjacent list (undirected)
            for (int j = 0; j < num; j++)
            {
                for (int k = j + 1; k < num; k++)
                {
                    relation[coauthor[j]].push_back(coauthor[k]);
                    relation[coauthor[k]].push_back(coauthor[j]);
                }
            }
        }

        erdos.assign(index, INF);
        erdos[ person["Erdos, P."] ] = 0;
        queue<int> Q;
        Q.push(person["Erdos, P."]);

        while(!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            for(int i = 0; i < relation[u].size(); i++)
            {
                int v = relation[u][i];
                if(erdos[v] == INF)
                {
                    erdos[v] = erdos[u] + 1;
                    Q.push(v);
                }
            }
        }

        cout << "Scenario " << scenIndex << endl;

        // input for query
        for (int i = 0; i < N; i++)
        {
            getline(cin, name);
            cout << name << " ";
            if (person.find(name) == person.end() || erdos[ person[name] ] == INF)
            {
                cout << "infinity" << endl;
            }
            else{
                cout << erdos[ person[name] ] << endl;
            }
        }
    }

    return 0;
}