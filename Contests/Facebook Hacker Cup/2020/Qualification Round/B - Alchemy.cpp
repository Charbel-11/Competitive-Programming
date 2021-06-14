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

	ifstream ifs("input.txt");
	ofstream ofs("out.txt");

	int t; ifs >> t;

	for (int qq = 1; qq <= t; qq++) {
		int n; ifs >> n;
		string s; ifs >> s;
		int a = 0, b = 0;
		for (int i = 0; i < n; i++) {
			a += s[i] == 'A';
			b += s[i] == 'B';
		}

		ofs << "Case #" << qq << ": " << (abs(a - b) == 1 ? 'Y' : 'N') << '\n';
	}
}