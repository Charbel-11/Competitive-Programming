#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> start, finish;

struct FT {
    int n; vector<ll> vals; FT(){}
    FT(const int n) : n(n), vals(vector<ll>(n + 1, 0)) { }

    //Adds x
    void update(int i, const ll x) {
        for (++i; i <= n; i += i & -i)
            vals[i] += x;
    }
    ll query(int i) const { // sum from 0 ... i
        assert(i >= -1 && i < n);
        ll sum = 0;
        for (++i; i; i -= i & -i)
            sum += vals[i];
        return sum;
    }
    ll query(int i, int j) const {		// sum from i ... j
        return query(j) - query(i - 1);
    }
};

struct edge {
    int u, v; edge() {}
    edge(int _u, int _v) :
            u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

//Everything is 0-indexed
struct tree {
    vector<vector<int>> anc;
    vector<node> nodes;
    vector<int> depth;
    vector<FT> vals;

    int root, n, lg2;

    tree(int _n, int _r = 0) : n(_n), root(_r) {
        lg2 = (int)(ceil(log2(n + 1.0)));
        nodes.resize(n); depth.resize(n, 0);
        anc.resize(n + 1, vector<int>(lg2 + 1, -1));
        vals = vector<FT>();
        for(int i = 0; i < 21; i++){ vals.push_back(FT(n)); }
        start.resize(n, -1); finish.resize(n, -1);
    }

    void add_edge(int u, int v) {
        edge e1(u, v); edge e2(v, u);
        nodes[u].edges.push_back(e1);
        nodes[v].edges.push_back(e2);
    }

    //Copy the constructor
    //Need to call this first
    //Preprocessing takes O(nlogn) time; finds the depth at the same time
    void preprocess() {
        queue<int> q; q.push(root);
        vector<bool> visited(n, false);
        visited[root] = true;
        anc[root][0] = root;

        while (!q.empty()) {
            int cur = q.front(); q.pop();
            for (auto &e : nodes[cur].edges) {
                if (visited[e.v]) { continue; }
                anc[e.v][0] = cur;
                depth[e.v] = depth[cur] + 1;
                q.push(e.v); visited[e.v] = true;
            }
        }
        for (int i = 1; i <= lg2; i++)
            for (int u = 0; u < n; u++)
                anc[u][i] = anc[anc[u][i - 1]][i - 1];
    }

    //Need to preprocess before using!
    //Returns the LCA of nodes u and v in O(logn)
    int LCA(int u, int v) {
        if (depth[u] < depth[v]) { swap(u, v); }

        for (int i = lg2; i >= 0; i--) {
            if (depth[u] - (1 << i) >= depth[v])
                u = anc[u][i];	//furthest parent found is 2^i
        }

        if (u == v) { return v; }

        for (int i = lg2; i >= 0; i--) {
            if (anc[u][i] != anc[v][i]) {
                u = anc[u][i];
                v = anc[v][i];
            }
        }

        return anc[u][0];
    }

    void preorder(int u, int &t) {
        start[u] = t++;
        for (auto &x : nodes[u].edges) {
            if (start[x.v] == -1) { preorder(x.v, t); }
        }
        finish[u] = t - 1;
    }

    ll getValue(int d, int v){
        return vals[d].query(start[v], finish[v]);
    }

    void addPathValue(int d, int u, int v, ll c){
        int l = LCA(u, v);
        vals[d].update(start[u], c);
        vals[d].update(start[v], c);
        vals[d].update(start[l], -c);
        if (l != root){
            vals[d].update(start[anc[l][0]], -c);
        }
    }
    void addNodeValue(int d, int u, ll c){
        vals[d].update(start[u], c);
        if (u != root){
            vals[d].update(start[anc[u][0]], -c);
        }
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n; cin >> n;
    tree t(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v; u--; v--;
        t.add_edge(u, v);
    }

    t.preprocess();
    int T = 0;
    t.preorder(0, T);

    int m; cin >> m;
    while(m--){
        int type; cin >> type;
        if (type == 1){
            int v; cin >> v; v--;
            ll ans = 0; int curP = v;
            for(int d = 0; d <= 20; d++){
                ans += t.getValue(d, curP);
                if (curP == 0){ break; }
                curP = t.anc[curP][0];
            }
            cout << ans << '\n';
        }
        else{
            int u, v, k, d; cin >> u >> v >> k >> d; u--; v--;
            t.addPathValue(d, u, v, k);

            int curP = t.LCA(u, v);

            bool skipFirst = false;
            t.addNodeValue(d, curP, -k);
            for(; d >= 0; d--){
                if (!skipFirst){ t.addNodeValue(d, curP, k); }
                if (d == 0){ break; }
                t.addNodeValue(d-1, curP, k);

                if (curP == 0){ skipFirst = true; }

                curP = t.anc[curP][0];
            }
        }
    }
}