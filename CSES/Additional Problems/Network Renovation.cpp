#include <iostream>
#include <vector>
#include <stack>
using namespace std;
 
vector<vector<int>> adj;
vector<int> leaves;
 
void dfs(int u, int p){
    if (adj[u].size() == 1){ leaves.push_back(u); }
    for (int v : adj[u]){
        if (v == p){ continue; }
        dfs(v, u);
    }
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
 
    int n; cin >> n;
    adj.resize(n);
    for(int i = 0; i < n - 1; i++){
        int u, v; cin >> u >> v; u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    dfs(0, -1);
    
    int m = leaves.size();
    cout << (m+1)/2 << '\n';
    for(int i = 0; i < m/2; i++){
        cout << leaves[i] + 1 << " " << leaves[i + (m+1)/2] + 1 << '\n';
    }
    if (m%2){
        cout << leaves[0] + 1 << " " << leaves[m/2] + 1 << '\n';
    }
}