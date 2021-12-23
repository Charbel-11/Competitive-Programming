//https://acm.timus.ru/problem.aspx?space=1&num=1041

#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
	ll res = 1;
	for (; p; p >>= 1, x = (x * x) % mod)
		if (p & 1) res = (res * x) % mod;
	return res;
}

// modular inverse (mod must be prime)
ll modinv(ll i) { return powe(i, mod - 2); }

vector<pair<int, int>> cost;
vector<int> pivot;

int GaussianElimination(vector<vector<ll>>& a, int row) {
	int n = a.size(), m = a[0].size();
	
	for (int col=0; col<m; col++) {
		if (a[row][col] == 0) { continue; }
		if (pivot[col] != -1) { continue; }
		
		for (int i = 0; i < n; i++) {
			if (i == row) { continue; }
			if (a[i][col] != 0) {
				ll c = (a[i][col] * modinv(a[row][col])) % mod;
				for (int j = col; j < m; j++) {
					ll diff = (a[row][j] * c) % mod;
					a[i][j] = (a[i][j] - diff + mod) % mod;
				}
			}
		}
		
		pivot[col] = row;
		return col;
	}
	
	return -1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	int m, n; cin >> m >> n;
	vector<vector<ll>> a(m, vector<ll>(n));
	for(int i = 0; i < m; i++)
		for(int j = 0; j < n; j++)
			cin >> a[i][j];
		
	cost.resize(m);
	for(int i = 0; i < m; i++){
		cin >> cost[i].first;
		cost[i].second = i;
	}
	sort(cost.begin(), cost.end());
	pivot.resize(n, -1);
	
	int totalCost = 0;
	vector<int> usedVec;
	for(int i = 0; i < m; i++){
		int res = GaussianElimination(a, cost[i].second);
		if (res != -1){
			totalCost += cost[i].first;
			usedVec.push_back(cost[i].second);
			if (usedVec.size() == n){ break; }
		}
	}
	
	if (usedVec.size() < n){ cout << 0 << '\n'; return 0; }
	
	sort(usedVec.begin(), usedVec.end());
	cout << totalCost << '\n';
	for(auto &x : usedVec) { cout << x + 1 << '\n'; }
}