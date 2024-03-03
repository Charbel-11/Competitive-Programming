#include <bits/stdc++.h>
using namespace std;
const int INF = 1 << 29;

struct edge {
    int u, v, w; edge() {}
    edge(int _u, int _v, int _w) :u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };
struct graph {
    vector<node> nodes;
    int n;

    graph(int _n) :n(_n) { nodes.resize(n); }

    void add_edge(int u, int v, int w) {
        edge e1(u, v, w);
        nodes[u].edges.push_back(e1);
    }

    //Assumes all weights are either 0 or x for a fixed x >= 0
    //Returns the shortest distance from s to all nodes
    vector<int> bfs01(int s) {
        vector<bool> visited(n, 0); vector<int> dist(n, INF); deque<int> dq;
        dist[s] = 0; dq.push_back(s);

        while (!dq.empty()) {
            int cur = dq.front(); dq.pop_front();
            while (visited[cur] && !dq.empty()) { cur = dq.front(); dq.pop_front(); }
            if (visited[cur]) { break; } visited[cur] = 1;

            for (auto &e : nodes[cur].edges) {
                if (visited[e.v] || dist[e.v] < dist[cur] + e.w) { continue; }
                dist[e.v] = dist[cur] + e.w;
                if (e.w) { dq.push_back(e.v); }
                else { dq.push_front(e.v); }
            }
        }

        return dist;
    }
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string s; cin >> s;
    map<pair<char, char>, int> dummyIdx; int idx = s.size() - 1;
    for(char i = 0; i < 26; i++){
        for(int j = 0; j < 26; j++){
            char cI = 'a' + i, cJ = 'a' + j;
            dummyIdx[{cI, cJ}] = idx++;
        }
    }

    graph g1(idx);
    for(int i = 0; i < s.size() - 1; i++){
        if (i + 1 < s.size() - 1) { g1.add_edge(i, i+1, 1); }
        if (i > 0){ g1.add_edge(i, i-1, 1); }
        char cI = s[i], cJ = s[i+1];
        int curDummyIdx = dummyIdx[{cI, cJ}];
        g1.add_edge(i, curDummyIdx, 1);
        g1.add_edge(curDummyIdx, i, 0);
    }

    idx = 0;
    vector dist1(26*26, vector<int>());
    for(char i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            dist1[idx] = g1.bfs01(s.size() - 1 + idx);
            idx++;
        }
    }

    int q; cin >> q;
    while(q--){
        int f, t; cin >> f >> t; f--; t--;
        int ans = abs(f - t);

        for(idx = 0; idx < 26*26; idx++) {
            ans = min(ans, dist1[idx][f] + dist1[idx][t] + 1);
        }

        cout << ans << '\n';
    }
}