#include <bits/stdc++.h>
using namespace std;
const int INF = 1 << 30;

struct node { vector<int> edges; };

struct bipartiteGraph {
    vector<node> nodes; int n, m;
    vector<int> level, match;

    bipartiteGraph(int _n, int _m) : n(_n), m(_m),
                                     nodes(_n + _m + 1), level(_n + 1), match(_n + _m + 1, 0) {}

    // u in [0,n-1], v in [n,n+m]
    void add_edge(int u, int v) {
        nodes[u + 1].edges.emplace_back(v + 1);
        nodes[v + 1].edges.emplace_back(u + 1);
    }

    bool getLevelGraph() {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        for (int i = 1; i <= n; i++){
            if (match[i] == 0) { level[i] = 0; q.push(i); }
        }

        while (!q.empty()) {
            int cur = q.front(); q.pop();
            for (auto &v : nodes[cur].edges) {
                if (level[match[v]] == -1) {
                    level[match[v]] = level[cur] + 1;
                    q.push(match[v]);
                }
            }
        }
        return (level[0] != -1);
    }

    bool matchingDFS(int cur) {
        if (cur == 0) { return true; }

        for (auto &v : nodes[cur].edges) {
            if (level[match[v]] != level[cur] + 1) { continue; }
            if (!matchingDFS(match[v])) { continue; }
            match[v] = cur;	match[cur] = v;
            return true;
        }
        level[cur] = INF; return false;
    }

    //O(Eroot(V)) worst case and O(Elog(V)) on average
    int maxMatching() {
        int res = 0;
        while (getLevelGraph()){
            for (int i = 1; i <= n; i++){
                if (match[i] != 0){ continue; }
                res += matchingDFS(i);
            }
        }
        return res;
    }
};

vector<int> docLevel, accessGroup;
struct graph{
    vector<node> nodes; int n;
    vector<int> inDegree;

    graph(int _n) : n(_n){
        nodes.resize(n);
        docLevel.resize(n, -1);
        accessGroup.resize(n, -1);
        inDegree.resize(n, 0);
    }

    void add_edge(int u, int v){
        nodes[u].edges.push_back(v);
        inDegree[v]++;
    }

    void dfsRec(int u, int level, int id){
        docLevel[u] = level;
        accessGroup[u] = id;
        for(auto v : nodes[u].edges){
            dfsRec(v, level+1, id);
        }
    }

    void dfs(){
        int id = 1;
        for(int i = 0; i < n; i++){
            if (inDegree[i] == 0){
                dfsRec(i, 2, id++);
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> req(n);
    for (auto &s: req) { cin >> s; }

    bipartiteGraph g(m, m);
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            bool zo = false, oz = false;
            for (int k = 0; k < n; k++) {
                if (req[k][i] == '1' && req[k][j] == '0') { oz = true; }
                if (req[k][i] == '0' && req[k][j] == '1') { zo = true; }
            }
            if (oz && zo) { continue; }
            if (zo) { g.add_edge(j, i + m); }
            else { g.add_edge(i, j + m); }
        }
    }

    int maxMatching = g.maxMatching();
    int numberAccessLevels = m - maxMatching;
    cout << numberAccessLevels << '\n';

    graph newG(m);
    for (int i = 1; i <= m; i++) {
        if (g.match[i]) {
            newG.add_edge(i - 1, g.match[i] - m - 1);
        }
    }
    newG.dfs();

    for(int j = 0; j < m; j++){ cout << accessGroup[j] << ' '; } cout << '\n';
    for(int j = 0; j < m; j++){ cout << docLevel[j] << ' '; }
    cout << '\n';

    for(int i = 0; i < n; i++){
        vector<int> curLevels(numberAccessLevels, 1);
        for(int j = 0; j < m; j++){
            if (req[i][j] == '1') {
                curLevels[accessGroup[j]-1] = max(curLevels[accessGroup[j]-1], docLevel[j]);
            }
        }

        for(auto& x : curLevels){ cout << x << ' '; }
        cout << '\n';
    }
}
