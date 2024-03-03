#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct StVal {
    int v = 0; StVal() {}
    StVal(const int _v) : v(_v) {}
    StVal(const StVal &v1, const StVal &v2) { v = v1 + v2; }
    operator int() const { return v; }	//Casts StVal to int
};

struct SegTree {
    int n;
    vector<int> leaves;
    vector<StVal> st;	//st[1] root; To go to a child, *2 (l) or *2+1 (r);	To go to a parent: /2

    SegTree(const int n) : n(n) {
        leaves.resize(n);
        init(1, 0, n - 1);
    }

    //lo, hi indices of the actual array; si is the index of the segment tree array
    void init(const int si, const int lo, const int hi) {
        if (lo == hi) {
            if (si >= (int)st.size()) { st.resize(si + 1); }
            st[si] = StVal();			//Set the actual array here
            leaves[lo] = si;
            return;
        }
        int lC = si << 1, rC = (si << 1) | 1, mid = (lo + hi) >> 1;
        init(lC, lo, mid); init(rC, mid + 1, hi);
        st[si] = StVal(st[lC], st[rC]);
    }

    //l and r inclusive, 0-indexed
    StVal query(const int l, const int r) { return (l <= r && l < n && r >= 0) ? query(l, r, 1, 0, n - 1) : StVal(); }
    StVal query(const int l, const int r, const int si, const int lo, const int hi) {
        if (l <= lo && hi <= r) return st[si];

        const int mid = (lo + hi) >> 1;
        if (r <= mid) return query(l, r, si << 1, lo, mid);
        if (mid < l) return query(l, r, si << 1 | 1, mid + 1, hi);
        return StVal(query(l, r, si << 1, lo, mid), query(l, r, si << 1 | 1, mid + 1, hi));
    }

    //Change a leaf and update its ancestors' values
    void update(const int i, int c) {
        int si = leaves[i];
        st[si] = StVal(c);
        for (si >>= 1; si; si >>= 1)
            st[si] = StVal(st[si << 1], st[si << 1 | 1]);
    }
};

struct edge {
    int u, v; edge() {}
    edge(int _u, int _v) :
            u(_u), v(_v) {}
};

struct node { int id; vector<edge> edges; };

vector<int> start, finish, order;
struct tree {
    vector<node> nodes;
    vector<int> depth, numLeaves;
    int n;

    tree(int _n): n(_n) {
        nodes.resize(n); start.resize(n, -1); finish.resize(n, -1);
        depth.resize(n, -1); numLeaves.resize(n, 0);
    }

    void add_edge(int u, int v) {
        edge e1(u, v), e2(v, u);
        nodes[u].edges.push_back(e1);
        nodes[v].edges.push_back(e2);
    }

    int preprocess(int u, int p, int d = 0){
        depth[u] = d; int curLeaves = 0;
        for(auto &e : nodes[u].edges){
            if (e.v == p){ continue; }
            curLeaves += preprocess(e.v, u, d + 1);
        }
        if (nodes[u].edges.size() == 1 && u != 0){ return numLeaves[u] = 1;}
        return numLeaves[u] = curLeaves;
    }

    void preorder(int u, int &t) {
        start[u] = t; t++; order.push_back(u);
        for (auto &x : nodes[u].edges) {
            if (start[x.v] == -1) { preorder(x.v, t); }
        }
        finish[u] = t - 1;
    }
};

void main_() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ifstream cin("in.txt");
    ofstream cout("out.txt");

    int t; cin >> t;
    for (int qq = 1; qq <= t; qq++) {
        start.clear(); finish.clear(); order.clear();
        int n; cin >> n; tree g(n);
        for(int i = 1; i < n; i++){
            int pi; cin >> pi; pi--;
            g.add_edge(i, pi);
        }
        g.preprocess(0, -1);
        int T = 0; g.preorder(0, T);

        map<string, vector<int>> wordToNodes;
        for(int i = 0; i < n; i++){
            int m; cin >> m;
            while(m--){
                string s; cin >> s;
                wordToNodes[s].push_back(i);
            }
        }

        int ans = 0; SegTree segT(n);
        for(auto &p : wordToNodes){
            vector<pair<int, int>> dN;
            for(auto &v : p.second){
                dN.emplace_back(g.depth[v], v);
            }
            sort(dN.rbegin(), dN.rend());

            vector<int> updates;
            bool OK = true;
            for(auto &pp : dN){
                int u = pp.second;
                int curLeaves = g.numLeaves[u];
                int doneLeaves = segT.query(start[u], finish[u]);
                curLeaves -= doneLeaves;
                if (curLeaves > 1){ OK = false; break; }
                else if (curLeaves == 1){
                    segT.update(start[u], 1);
                    updates.push_back(start[u]);
                }
            }

            int finalLeaves = g.numLeaves[0];
            int doneLeaves = segT.query(start[0], finish[0]);
            if (finalLeaves != doneLeaves){ OK = false; }

            ans += OK;
            for(auto &u : updates){ segT.update(u, 0); }
        }

        cout << "Case #" << qq << ": " << ans << '\n';
    }
}


static void run_with_stack_size(void (*func)(void), size_t stsize) {
    char *stack, *send;
    stack = (char *)malloc(stsize);
    send = stack + stsize - 16;
    send = (char *)((uintptr_t)send / 16 * 16);
    asm volatile(
            "mov %%rsp, (%0)\n"
            "mov %0, %%rsp\n"
            :
            : "r"(send));
    func();
    asm volatile("mov (%0), %%rsp\n" : : "r"(send));
    free(stack);
}
int main() {
    run_with_stack_size(main_, 1024 * 1024 * 1024); // run with a 1 GiB stack
    return 0;
}