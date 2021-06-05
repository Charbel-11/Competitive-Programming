#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	ll ss = (ll)n*(n + 1) / 2;
	if (ss % 2) { cout << "NO\n"; return 0; }

	vector<int> s1, s2;
	int l = 1, r = n;
	if (n % 2) { s1.push_back(1); s1.push_back(n - 1); s2.push_back(n); l++; r -= 2; }

	//Guaranteed to have an even amount of pairs (otherwise n of the form 3 + 2(2k+1) which can be proven to give ss%2==1)
	bool alt = 1;
	while (l < r) {
		if (alt) { s1.push_back(l); s1.push_back(r); }
		else { s2.push_back(l); s2.push_back(r); }
		l++; r--; alt = !alt;
	}

	cout << "YES\n";
	cout << s1.size() << '\n';
	for (auto &x : s1) { cout << x << ' '; } cout << '\n';
	cout << s2.size() << '\n';
	for (auto &x : s2) { cout << x << ' '; } cout << '\n';
}