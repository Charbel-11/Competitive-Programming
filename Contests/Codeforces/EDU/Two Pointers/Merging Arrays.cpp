#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	int n, m; cin >> n >> m;
	vector<int> a(n); for(auto &x : a){ cin >> x; }
	vector<int> b(m); for(auto &x : b){ cin >> x; }
	
	vector<int> c(n+m);
	merge(a.begin(), a.end(), b.begin(), b.end(), c.begin());
	
	for(auto &x : c) { cout << x << ' '; }
	cout << '\n';
}