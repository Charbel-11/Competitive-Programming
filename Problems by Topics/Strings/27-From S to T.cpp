//https://codeforces.com/problemset/problem/1194/C
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int q;
	cin >> q;

	for (int z = 0; z < q; z++) {
		string s, t, p;		//t fixed
		cin >> s >> t >> p;

		if (s.size() > t.size()) {
			cout << "NO" << endl;
			continue;
		}

		vector<int> freq(26, 0);

		for (int i = 0; i < p.size(); i++) {
			freq[p[i] - 'a']++;
		}

		int sI = 0;
		int tI = 0;
		bool OK = true;

		while (tI < t.size()) {
			if (t[tI] == s[sI]) {
				tI++;
				sI++;
			}
			else if (freq[t[tI] - 'a'] > 0) {
				freq[t[tI] - 'a']--;
				tI++;
			}
			else {
				OK = false;
				break;
			}
		}

		if (sI < s.size()) {			//Imp
			OK = false;
		}

		if (OK) {
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
}