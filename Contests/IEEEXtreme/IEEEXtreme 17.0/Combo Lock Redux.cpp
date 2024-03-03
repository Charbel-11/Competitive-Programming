#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1000 * 1000 * 1000 + 9;

struct Edge {
    int u, v; Edge() {}
    Edge(int _u, int _v) :
            u(_u), v(_v) {}
};

struct Node { vector<Edge> edges; };
struct Graph {
    vector<Node> nodes;
    int n;

    Graph(int _n) : n(_n) { nodes.resize(n); }

    void addEdge(int u, int v) {
        Edge e1(u, v); nodes[u].edges.push_back(e1);
        Edge e2(v, u); nodes[v].edges.push_back(e2);
    }

    int bfs(int s, int t, vector<ll>& dp){
        vector<int> dist(n, -1); dist[s] = 0;
        queue<int> Q; vector<bool> vis(n, false);
        Q.push(s); vis[s] = true; dp[s] = 1;

        while(!Q.empty()){
            int cur = Q.front(); Q.pop();
            for(auto &e : nodes[cur].edges){
                if (vis[e.v]){
                    if (dist[e.u] + 1 == dist[e.v]){
                        dp[e.v] += dp[e.u];
                        dp[e.v] %= mod;
                    }
                    continue;
                }
                vis[e.v] = true; Q.push(e.v);
                dist[e.v] = dist[e.u] + 1;
                assert(dp[e.v] == 0);
                dp[e.v] += dp[e.u]; dp[e.v] %= mod;
            }
        }

        return dist[t];
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int c; cin >> c;
    while(c--){
        int n; string st; cin >> n >> st;
        ll h0, a, b, q; cin >> h0 >> a >> b >> q;

        int numStates = 1, t = stoi(st);
        for(int i = 0; i < n; i++){ numStates *= 10; }

        set<int> neighborsOfT;
        for(int j = 0; j < n; j++) {
            if (st[j] < '9') { st[j]++; }
            else{ st[j] = '0'; }
            neighborsOfT.insert(stoi(st));

            if (st[j] == '0') { st[j] = '9'; }
            else{ st[j]--; }

            if (st[j] > '0'){ st[j]--; }
            else{ st[j] = '9'; }
            neighborsOfT.insert(stoi(st));

            if (st[j] == '9') { st[j] = '0'; }
            else{ st[j]++; }
        }

        set<ll> seen;
        vector<bool> available(numStates, 0);
        while (!seen.count(h0)){
            seen.insert(h0);
            available[(h0 % numStates)] = true;
            if (neighborsOfT.count((h0 % numStates))) { break; }
            h0 = (a * h0 + b) % q;
        }
        available[0] = true; available[t] = true;

        Graph g(numStates);
        for(int i = 0; i < numStates; i++){
            if (!available[i]){ continue; }
            string s = to_string(i);
            reverse(s.begin(), s.end());
            while(s.size() < n){ s.push_back('0'); }
            reverse(s.begin(), s.end());

            for(int j = 0; j < n; j++){
                if (s[j] < '9') { s[j]++; }
                else{ s[j] = '0'; }
                int intState = stoi(s);
                if (available[intState]){ g.addEdge(i, intState); }

                if (s[j] == '0') { s[j] = '9'; }
                else{ s[j]--; }
            }
        }

        vector<ll> dp(numStates, 0);
        int minP = g.bfs(0, t, dp);
        cout << minP;
        if (minP != -1){ cout << ' ' << dp[t] << '\n'; }
        else{ cout << '\n'; }
    }
}

