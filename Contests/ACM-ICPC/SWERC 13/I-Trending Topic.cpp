#include <string>
#include <map>
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

map<string, int> freq;
vector<map<string, int>> last7;

struct compare {
	bool operator()(const pair<int, string> &p1, const pair<int, string> &p2) {
		if (p1.first == p2.first) { return p2.second < p1.second; }
		return p1.first < p2.first;
	}
};

void query(int N) {
	cout << "<top " << N << ">" << endl;
	set<pair<int, string>, compare> res;
	for (auto x : freq) { res.insert({ x.second, x.first }); }

	int cur = 0; int last;
	for (auto it = res.rbegin(); it != res.rend(); it++) {
		if (cur == N) { 
			it--; last = it->first; it++;
			while (it != res.rend() && it->first == last) { cout << it->second << ' ' << it->first << endl; it++; }
			break; 
		}
		cout << it->second << ' ' << it->first << endl; cur++;
	}

	cout << "</top>" << endl;
}

void removeDay(int i) {
	for (auto &x : last7[i]) { freq[x.first] -= x.second; }
}

int main() {
	last7.resize(7);
	int day = 0; string s;
	while (true) {
		cin >> s; if (cin.fail()) { break; }
		if (s != "<text>") {
			int N; cin >> N; cin >> s;
			query(N); continue;
		}
		removeDay(day);	last7[day].clear();
		while (true) {
			cin >> s;
			if (s == "</text>") { break; }
			if ((int)s.size() < 4) { continue; }
			freq[s]++; last7[day][s]++;
		}
		day++; day %= 7;
	}
}