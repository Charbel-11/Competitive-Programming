#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Graph{
    vector<vector<int>> edges; int n;
    Graph(int _n): n(_n) { edges.resize(n); }
    void addEdge(int u, int v){
        edges[u].emplace_back(v);
    }

    vector<bool> BFS(int start){
        vector<bool> reachable(n, false);
        reachable[start] = true;
        queue<int> Q; Q.push(start);

        while(!Q.empty()){
            int cur = Q.front(); Q.pop();
            for(auto v : edges[cur]){
                if (reachable[v]){ continue; }
                reachable[v] = true; Q.push(v);
            }
        }

        return reachable;
    }
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int m, n; cin >> m >> n;
    Graph G(26);
    for(int i = 0; i < m; i++){
        char u, v; cin >> u >> v;
        G.addEdge(u-'a', v-'a');
    }

    vector<vector<bool>> reachable;
    for(int i = 0; i < 26; i++){
        reachable.push_back(G.BFS(i));
    }

    for(int i = 0; i < n; i++){
        string w1, w2; cin >> w1 >> w2;
        if (w1.size() != w2.size()) { cout << "no\n"; }
        else{
            bool OK = true;
            for(int j = 0; j < w1.size(); j++){
                if (!reachable[w1[j]-'a'][w2[j]-'a']){
                    OK = false; break;
                }
            }
            if (OK){ cout << "yes\n"; }
            else { cout << "no\n"; }
        }
    }
}

