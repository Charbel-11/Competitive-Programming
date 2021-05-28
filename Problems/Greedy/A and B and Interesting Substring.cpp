#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>

using namespace std;

int main() {
	vector<int> val(26);
	for (auto &x : val) { cin >> x; }

	string s; cin >> s;
	vector<vector<int>> occ(26);
	vector<long long> partial(s.size(), 0);

	for (int i = 0; i < s.size(); i++) {
		occ[s[i] - 'a'].push_back(i);

		partial[i] = val[s[i] - 'a'];
		if (i) partial[i] += partial[i - 1];
	}

	long long res = 0;
	for (int i = 0; i < 26; i++) {
		map<long long, int> m;

		for (int j = 0; j < occ[i].size(); j++) {
			int idx = occ[i][j];
			if (idx) { res += m[partial[idx - 1]]; }
			m[partial[idx]]++;
		}
	}

	cout << res << endl;
}