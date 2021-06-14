//https://codeforces.com/contest/1183/problem/H
#include <string>
#include <iostream>
#include <set>

using namespace std;
typedef long long ll;

ll DP[102][102];
string s; int n;

ll count(int i, int j) {
	if (DP[i][j] != -1) { return DP[i][j]; }
	if (i == 0) { return DP[i][j] = 1; }
	if (j >= n) { return 0; }

	set<char> used; ll res = 0;
	for (int k = j; k < n - i + 1; k++) {
		char &c = s[k];
		if (used.count(c) != 0) { continue; }
		
		used.insert(c);
		res += count(i - 1, k + 1);
	}

	return DP[i][j] = res;
}

void resetDP() {
	for (int i = 0; i < 102; i++)
		for (int j = 0; j < 102; j++)
			DP[i][j] = -1;
}

int main() {
	ll k; cin >> n >> k;
	cin >> s;
	resetDP();

	ll used = 0, cost = 0;
	int i = n;
	while (true) {
		used = count(i, 0);
		if (used < k) { 
			cost += used * (n - i);
			k -= used; used = 0; 
		}
		else {
			cost += k * (n - i); 
			k = 0; break;
		}
		i--; if (i == -1) { break; }
	}

	if (k > 0) { cout << -1 << endl; }
	else { cout << cost << endl; }
}