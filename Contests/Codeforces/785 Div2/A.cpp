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

	int t; cin >> t;
	while (t--) {
		string s; cin >> s;
		int alice = 0;
		for (auto& c : s) { alice += c - 'a' + 1; }
		
		int sc0 = s[0] - 'a' + 1, scn = s.back() - 'a' + 1;
		if (s.size() % 2 == 1) { alice -= min(sc0, scn) * 2; }

		if (alice > 0) { cout << "Alice " << alice << '\n'; }
		else { cout << "Bob " << -alice << '\n'; }
	}
}