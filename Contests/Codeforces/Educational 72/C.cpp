#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <bitset>

using namespace std;
typedef long long ll;

int main() {
	int t; cin >> t;

	vector<int> numsToZeros(2 * 1e5 + 2);
	int pow2 = 2; int counter = 0;
	for (int i = 1; i <= 2 * 1e5 + 1; i++) {
		numsToZeros[i] = counter;
		if (i + 1 == pow2) { pow2 *= 2; }
		else { counter++; }
	}

	map<int, vector<int>> zeros;
	for (int i = 1; i <= 2 * 1e5 + 1; i++) {
		zeros[numsToZeros[i]].push_back(i);
	}

	vector<string> binaryS(2 * 1e5 + 2);
	for (int i = 1; i <= 2 * 1e5 + 1; i++) {
		string temp = bitset<27>(i).to_string();
		string f = ""; bool b = true;
		for (int i = 0; i < temp.size(); i++) {
			if (b) { while (temp[i] == '0') { i++;  b = false; } }
			f.push_back(temp[i]);
		}
		binaryS[i] = f;
	}

	for (int z = 0; z < t; z++) {
		string s; cin >> s;

		ll res = 0;

		int curZero = 0;
		for (int i = 0; i < s.size(); i++) {
			while (i < s.size() && s[i] == '0') { curZero++; i++; }
			if (i == s.size()) { break; }

			int j = zeros[curZero].back();
			while (j > 0) {
				if (s.substr(i, binaryS[j].size()) == binaryS[j]) { res++; }
				j--;
			}

			curZero = 0;
		}

		cout << res << endl;
	}
}