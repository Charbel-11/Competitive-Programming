#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stack>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		string s; cin >> s;
		vector<char> st;

		for (int i = 0; i < n; i++) {
			if (st.empty() || st.back() == s[i] || s[i] == '1') { st.push_back(s[i]); continue; }
			while (!st.empty() && st.back() != s[i]) {
				st.pop_back(); 
			}
			st.push_back(s[i]);
		}

		vector<int> zerosS(n, 0), onesP(n,0);
		for (int i = n - 1; i >= 0; i--) { zerosS[i] = (i < n - 1 ? zerosS[i + 1] : 0) + (s[i] == '0');	}
		for (int i = 0; i < n; i++) { onesP[i] = (i ? onesP[i - 1] : 0) + (s[i] == '1'); }

		int rem = 0;
		for (int i = 0; i < n; i++) {
			if (s[i] == '0' && zerosS[i] > 1 && onesP[i]) { rem++; }
		}

		for (auto &x : st) {
			if (rem) { rem--; continue; }
			cout << x;
		}
		cout << '\n';
	}
}