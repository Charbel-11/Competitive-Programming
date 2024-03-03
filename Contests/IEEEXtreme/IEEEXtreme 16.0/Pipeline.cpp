#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
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

int dx[]={0,0,1};
int dy[]={0,1,0};
int dz[]={1,0,0};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while(t--){
        int n, m, d; cin >> n >> m >> d;
        vector<vector<vector<vector<int>>>> nodes(d, vector<vector<vector<int>>>(n, vector<vector<int>>(m)));

        int numEven = 0, numOdd = 0;
        for(int i = 0; i < d; i++){
            for(int j = 0; j < n; j++){
                string s; cin >> s;
                for(int k = 0; k < m; k++){
                    bool curEven = ((i+j+k) % 2) == 0;
                    if (s[k] == '#'){ continue; }

                    int numNodes = 0;
                    if (s[k] == '*'){ numNodes = 3; }
                    else if (s[k] == 'o') { numNodes = 2; }

                    if (curEven) {
                        for(int mm = 0; mm < numNodes; mm++)
                            nodes[i][j][k].push_back(numEven+mm);
                        numEven += numNodes;
                    }
                    else {
                        for(int mm = 0; mm < numNodes; mm++)
                            nodes[i][j][k].push_back(numOdd+mm);
                        numOdd += numNodes;
                    }
                }
            }
        }

        if ((numEven + numOdd) & 1){ cout << "NO\n"; continue; }

        bipartiteGraph g(numEven, numOdd);

        for(int i = 0; i < d; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < m; k++) {
                    bool curEven = ((i+j+k) % 2) == 0;
                    for(int tt = 0; tt < 3; tt++){
                        int ni = i + dz[tt], nj = j + dx[tt], nk = k + dy[tt];
                        if (ni >= d || nj >= n || nk >= m) { continue; }

                        for(auto &u : nodes[i][j][k]){
                            for(auto &v : nodes[ni][nj][nk]){
                                if (curEven){ g.add_edge(u, v + numEven); }
                                else{ g.add_edge(v, u + numEven); }
                            }
                        }
                    }
                }
            }
        }

        int mm = g.maxMatching();
        if (mm == (numEven+numOdd)/2){ cout <<"YES\n"; }
        else { cout <<"NO\n"; }
    }
}