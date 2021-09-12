#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream ifs("in.txt");
	ofstream ofs("out.txt");

	int t; ifs >> t;
	for (int qq = 1; qq <= t; qq++) {
		int n; ifs >> n;
		string w; ifs >> w;

		string s = "";
		for (auto& c : w) {
			if (c != 'F') { s.push_back(c); }
		}

		int ans = 0;
		for (int i = 1; i < s.size(); i++) {
			if (s[i] != s[i - 1]) { ans++; }
		}

		ofs << "Case #" << qq << ": " << ans << '\n';
	}
}