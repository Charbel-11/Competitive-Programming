#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct edge {
    int u, v; edge() {}
    edge(int _u, int _v) :
            u(_u), v(_v) {}
};

struct node {
    int color = 0, dpCopy = -1, extraBlack = 0, extraWhite = 0;
    vector<edge> edges;
    vector<int> dp;
};

struct tree {
    vector<node> nodes;
    int root, n;

    tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); }

    void add_edge(int u, int v) {
        edge e1(u, v), e2(v, u);
        nodes[u].edges.push_back(e1);
        nodes[v].edges.push_back(e2);
    }

    int dfs(int u, int p){
        int minDepth = n;
        for(auto &e : nodes[u].edges){
            if (e.v == p){ continue; }
            int curDepth = dfs(e.v, u);
            minDepth = min(minDepth, curDepth + 1);
        }

        int numChildren = nodes[u].edges.size() - 1;
        if (u == 0){
            numChildren++;
        }
        if (numChildren == 0){
            minDepth = 1;
            if (nodes[u].color == 1){ nodes[u].dp = {1, 0}; }
            else{ nodes[u].dp = {0, 1}; }
        }
        else if (numChildren == 1){
            for(auto &e : nodes[u].edges){
                if (e.v == p){ continue; }
                if (nodes[u].color == 1){ nodes[u].extraBlack++; }
                else{ nodes[u].extraWhite++; }
                nodes[u].extraBlack += nodes[e.v].extraBlack;
                nodes[u].extraWhite += nodes[e.v].extraWhite;

                nodes[u].dpCopy = e.v;
                if (nodes[e.v].dpCopy != -1){
                    nodes[u].dpCopy = nodes[e.v].dpCopy;
                }
            }
        }
        else{
            for(int i = 0; i < minDepth+1; i++){
                nodes[u].dp.push_back(n);
            }

            for(int curStart = 0; curStart <= 1; curStart++) {
                int curCount = 1 - nodes[u].color;
                if (curStart == 0){ curCount = nodes[u].color; }

                for (int j = curCount; j <= minDepth; j++) {
                    int curCost = curStart, needed = j - curCount;
                    for (auto &e: nodes[u].edges) {
                        if (e.v == p) { continue; }
                        if (nodes[e.v].dpCopy != -1) {
                            int proxyDP = nodes[e.v].dpCopy;
                            int proxyDPSize = nodes[proxyDP].dp.size();

                            int realMax = proxyDPSize - 1 + nodes[e.v].extraWhite + nodes[e.v].extraBlack;
                            if (realMax < needed) { curCost = n; break; }

                            int curcurCost = n;
                            for (int blackFromLine = 0; blackFromLine <= nodes[e.v].extraWhite + nodes[e.v].extraBlack; blackFromLine++) {
                                if (blackFromLine > needed) { break; }
                                int payForLine = abs(blackFromLine - nodes[e.v].extraBlack);
                                if (nodes[proxyDP].dp.size() <= needed-blackFromLine){ continue; }
                                int remainingPay = nodes[proxyDP].dp[needed - blackFromLine];

                                curcurCost = min(curcurCost, payForLine + remainingPay);
                            }
                            curCost += curcurCost;
                        } else {
                            curCost += nodes[e.v].dp[needed];
                        }
                    }
                    nodes[u].dp[j] = min(nodes[u].dp[j], curCost);
                }
            }
        }

        return minDepth;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int tt; cin >> tt;
    while(tt--){
        int n; cin >> n;
        tree t(n); string s; cin >> s;
        for(int i = 0; i < n; i++){
            if (s[i] == '1') { t.nodes[i].color = 1; }
        }
        for (int i = 0; i < n - 1; i++) {
            int p; cin >> p; p--;
            t.add_edge(i+1, p);
        }

        t.dfs(0, -1);
        for(int i = 0; i < n; i++){
            int cur = i;
            if (t.nodes[cur].dpCopy != -1){ cur = t.nodes[cur].dpCopy; }
            if(t.nodes[cur].dp.empty()){ cout << 0 << '\n'; }
            else cout << *min_element(t.nodes[cur].dp.begin(), t.nodes[cur].dp.end()) << ' ';
        }
        cout << '\n';
    }
}