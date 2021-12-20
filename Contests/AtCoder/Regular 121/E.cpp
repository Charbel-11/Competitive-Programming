#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=998244353;

ll fact[2002];
ll dp[2002][2002];

void buildFact(){
	fact[0]=1;
	for(int i=1;i<=2000;i++){
		fact[i]=(fact[i-1]*i)%mod;
	}
}

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
			u(_u), v(_v) {}
};
struct node { vector<edge> edges; };
struct tree {
	vector<node> nodes;
	vector<int> subtreeSize;
	int n;
	
	tree(int _n) : n(_n) {
		nodes.resize(n);
		subtreeSize.resize(n, 1);
	}
	
	void add_edge(int u, int v) {
		edge e1(u, v), e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}
	
	void dfs(int u, int p = -1) {
		dp[u][0] = 1;
		
		int firstChildIdx = -1;
		for (auto &e: nodes[u].edges) {
			if (e.v == p){ continue; }
			
			dfs(e.v, e.u);
			if (firstChildIdx == -1){
				firstChildIdx = e.v;
			}
		}
		if (firstChildIdx == -1) { return; }
		
		subtreeSize[u] += subtreeSize[firstChildIdx];
		for (int j = subtreeSize[u]; j >= 1; j--) {
			dp[u][j] = dp[firstChildIdx][j];
		}
		
		for(auto &e : nodes[u].edges){
			if (e.v == p || e.v == firstChildIdx) { continue; }
			subtreeSize[u] += subtreeSize[e.v];
			
			for (int j = subtreeSize[u]; j >= 1; j--) {
				for (int i = 1; i <= min(subtreeSize[e.v], j); i++) {
					dp[u][j] += dp[u][j - i] * dp[e.v][i]; dp[u][j] %= mod;
				}
			}
		}
		
		for (int j = subtreeSize[u]; j >= 1; j--) {
			dp[u][j] += dp[u][j - 1] * (subtreeSize[u] - 1 - (j - 1)); dp[u][j] %= mod;
		}
	}
};

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	ll n; cin>>n;
	tree t(n);
	for(int i=1; i<n; i++){
		int u; cin >> u; u--;
		t.add_edge(u, i);
	}
	
	buildFact();
	t.dfs(0);
	
	ll ans = fact[n];
	for(int i=1; i<=n; i++){
		ll cur = dp[0][i]*fact[n-i]; cur%=mod;
		if(i%2 == 1){ cur = -cur + mod; }
		
		ans += cur; ans %= mod;
	}
	
	cout << ans << '\n';
}