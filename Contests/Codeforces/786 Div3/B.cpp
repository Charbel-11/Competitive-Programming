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

	map<string, int> m;
	int idx = 1;
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			if (i == j) { continue; }

			char c1 = 'a' + i, c2 = 'a' + j;
			string cur = "";
			cur.push_back(c1); cur.push_back(c2);
			m[cur] = idx++;
		}
	}

	int t; cin >> t;
	while (t--) {
		string s; cin >> s;
		cout << m[s] << '\n';
	}
}