#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

int lg = 31;    //Change if needed
vector<vector<int>> anc;
vector<bool> vis, inCycle;
vector<int> len;    //len[i] = dist from i to the start of the cycle (the start could be any point on the cycle)

void dfs(int s) {
    if (vis[s]) { return; }
    vis[s] = 1;
    dfs(anc[s][0]);
    len[s] = len[anc[s][0]] + 1;
}
void markCycle(int u) {
    if (inCycle[u]) { return; }
    inCycle[u] = true;
    markCycle(anc[u][0]);
}
int toKth(int x, int k) {
    if (k <= 0) { return x; }
    int i = 0;
    while (k) {
        if (k & 1) { x = anc[x][i]; }
        k >>= 1; i++;
    }
    return x;
}
//Finds the first node inCycle by following the path that starts at u
//Note that len[cycleStart] != length of the cycle
int findFirstCycleNode(int u) {
    if (inCycle[u]) { return u; }
    int i = lg;
    while (i >= 0) {
        if (!inCycle[anc[u][i]]) { u = anc[u][i]; }
        i--;
    }
    return anc[u][0];
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n; cin >> n;
    anc.resize(n, vector<int>(lg + 1));
    vis.resize(n, 0); len.resize(n, 0);
    inCycle.resize(n, 0);

    for (int i = 0; i < n; i++) {
        int v; cin >> v; v--;
        anc[i][0] = v;
    }

    for (int i = 1; i <= lg; i++)
        for (int u = 0; u < n; u++)
            anc[u][i] = anc[anc[u][i - 1]][i - 1];

    for (int i = 0; i < n; i++) {
        if (!vis[i]) { 
            dfs(i);
            int cycleRoot = toKth(i, len[i]);
            if (!inCycle[cycleRoot]) { markCycle(cycleRoot); }
        }
    }

    for (int i = 0; i < n; i++) {
        int cycleRoot = toKth(i, len[i]);
        int cycleStart = findFirstCycleNode(i);
        cout << len[i] - len[cycleStart] + len[cycleRoot] << ' ';
    }
}