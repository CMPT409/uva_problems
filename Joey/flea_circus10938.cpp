#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <list>

using namespace std;

#define INF 0X7FFFFFFF

int distance(int a, int b, int N, list<int> adjacentLists[], int* path)
{
    int dis[N+1];
    for (size_t i = 0; i <= N; i++) {
        dis[i] = INF;
        path[i] = -1;
    }
    dis[a] = 0;
    if (a == b) {
        return 0;
    }
    queue<int> q;
    q.push(a);
    int stop = 0;
    while(!q.empty() && !stop){
        int v = q.front();
        q.pop();
        for (list<int>::iterator it = adjacentLists[v].begin(); it != adjacentLists[v].end(); it++) {
            if (dis[*it] == INF) {
                dis[*it] = dis[v] + 1;
                q.push(*it);
                path[*it] = v;
                if(*it == b){
                    stop = 1;
                    break;
                }
            }
        }
    }
    return dis[b];
}

int main(int argc, char const *argv[]) {
    while (true) {
        int N;
        cin >> N;
        if (N == 0) {
            break;
        }
        list<int> adjacentLists[N+1];
        for (size_t i = 0; i < N - 1; i++) {
            int v1, v2;
            cin >> v1 >> v2;
            adjacentLists[v1].push_back(v2);
            adjacentLists[v2].push_back(v1);
        }
        int queryNum;
        cin >> queryNum;
        for (size_t i = 0; i < queryNum; i++) {
            int start1, start2;
            cin >> start1 >> start2;
            int path[N+1];
            int dis = distance(start1, start2, N, adjacentLists, path);
            if (dis == 0) {
                cout << "The fleas meet at " << start1 << "." << endl;
            }
            else if (dis%2 == 0) {
                //meet
                int meetPoint = start2;
                for (size_t j = 0; j < dis/2 ; j++) {
                    meetPoint = path[meetPoint];
                }
                cout << "The fleas meet at " << meetPoint << "."<< endl;
            }
            else {
                //jump forever
                int jumpPoint2 = start2;
                for (size_t j = 0; j < dis/2; j++) {
                    jumpPoint2 = path[jumpPoint2];
                }
                int jumpPoint1 = path[jumpPoint2];
                if (jumpPoint1 > jumpPoint2) {
                    int temp = jumpPoint1;
                    jumpPoint1 = jumpPoint2;
                    jumpPoint2 = temp;
                }
                cout << "The fleas jump forever between " << jumpPoint1 << " and " << jumpPoint2 << "." << endl;
            }
        }
    }
    return 0;
}
