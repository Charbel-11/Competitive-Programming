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

	int n; cin >> n;
	map<string, int> m;
	for (int i = 0; i < n; i++) {
		string s; cin >> s; m[s]++;
	}

	for(auto &p : m){
		if (p.second > n / 2) { cout << p.first << '\n'; return 0; }
	}
	cout << "NONE" << '\n';
}