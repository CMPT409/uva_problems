#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <set>
using namespace std;

void bfs(const string& start, vector<list<string>>& lists,
         map<string, int>& m, map<string, int>& erdosNums) {
    queue<string> que;
    que.push(start);
    que.push("");
    erdosNums[start] = 1;
    int count = 1;
    while(!que.empty()) {
        int idx = m[que.front()];
        int flag = 0;
        que.pop();
        if (que.front() == "") {
            que.pop();
            flag = 1;
        }
        for (list<string>::iterator it = lists[idx].begin(); it != lists[idx].end(); it++) {
            if(erdosNums[*it] != 0){
                continue;
            }
            erdosNums[*it] = count;
            que.push(*it);
        }
        if (flag == 1) {
            if (que.empty()) {
                break;
            }
            que.push("");
            count++;
        }
    }
}

int main(int argc, char const *argv[]) {
    int repeat;
    cin >> repeat;
    for (int ri = 0; ri < repeat; ri++) {
        cout << "Scenario " << ri + 1 << endl;
        int paperNum;
        int queryNum;
        vector<list<string>> lists;
        map<string, int> m;
        vector<string> queries;
        cin >> paperNum >> queryNum;
        getchar();
        for (int i = 0; i < paperNum; i++) {
            vector<string> coauthors;
            string name;
            int flag = 0;
            string str;
            char* tokens;
            getline(cin, str);
            str = str.replace(str.find_first_of(":"), string::npos, "");
            int len = str.length();
            char c_str[len + 1];
            strcpy(c_str, str.c_str());
            tokens = strtok(c_str, ", ");
            while (tokens != NULL) {
                if (flag == 0) {
                    name += tokens;
                    name += ", ";
                    flag = 1;
                }
                else {
                    name += tokens;
                    coauthors.push_back(name);
                    if (m.find(name) == m.end()) {
                        list<string> l;
                        lists.push_back(l);
                        m[name] = lists.size() - 1;
                    }
                    name.clear();
                    flag = 0;
                }
                tokens = strtok(NULL, ", ");
            }
            for (int j = 0; j < coauthors.size(); j++) {
                string addListName1 = coauthors[j];
                for (int k = j + 1; k < coauthors.size(); k++){
                    string addListName2 = coauthors[k];
                    lists[m[addListName1]].push_back(addListName2);
                    lists[m[addListName2]].push_back(addListName1);
                }
            }
        }
        for (int j = 0; j < queryNum; j++) {
            string queryName;
            getline(cin, queryName);
            queries.push_back(queryName);
        }
        map<string, int> erdosNums;
        bfs("Erdos, P.", lists, m, erdosNums);
        for(int j = 0; j < queries.size(); j++) {
            if (erdosNums[queries[j]] == 0) {
                cout << queries[j] << " infinity" << endl;
            }
            else{
                cout << queries[j] << " " << erdosNums[queries[j]] << endl;
            }
        }
    }
    return 0;
}
