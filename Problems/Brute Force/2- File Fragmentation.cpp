//https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1073
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <set>

using namespace std;

vector<string> fragments;

string file(int size) {
	int n = fragments.size();

	map<string, int> freq;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (fragments[i].length() + fragments[j].length() != size) { continue; }

			freq[fragments[i] + fragments[j]]++;
			freq[fragments[j] + fragments[i]]++;
		}
	}

	int curMax = 0; string res = "";
	for (auto itr = freq.begin(); itr != freq.end(); itr++) {
		if (itr->second > curMax) {
			curMax = itr->second;
			res = itr->first;
		}
	}
	if (res == "") { return fragments[0] + fragments[0]; }
	return res;
}

int main() {
	set<string> dup;
	int n; cin >> n;
	string s;
	getline(cin, s);
	getline(cin, s);

	for (int i = 0; i < n; i++) {
		fragments.clear();
		dup.clear();
		int size = 0, realNum = 0;

		while (getline(cin, s) && !s.empty()) {
			size += s.length();
			realNum++;
			if (dup.count(s) == 0) {
				fragments.push_back(s);
				dup.insert(s);
			}
		}

		size = size / (realNum / 2);
		cout << file(size) << endl;
		if (i + 1 != n) { cout << endl; }
	}

	return 0;
}