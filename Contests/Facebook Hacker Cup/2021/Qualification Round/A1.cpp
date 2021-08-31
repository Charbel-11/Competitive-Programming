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

const set<int> vowels = { 'A', 'E', 'I', 'O', 'U' };

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream ifs("in.txt");
	ofstream ofs("out.txt");

	int t; ifs >> t;
	for (int qq = 1; qq <= t; qq++) {
		string s; ifs >> s;
		int ans = s.size() * 2;

		for (char c = 'A'; c <= 'Z'; ++c) {
			int curAns = 0;
			for (auto& curC : s) {
				if (curC == c) { continue; }
				if ((vowels.count(curC) ^ vowels.count(c)) == 1) { curAns++; }
				else { curAns += 2; }
			}
			ans = min(ans, curAns);
		}

		ofs << "Case #" << qq << ": " << ans << '\n';
	}
}