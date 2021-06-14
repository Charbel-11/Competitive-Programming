#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	string s, t;
	cin >> s >> t;
	int n = t.size();
	vector<int> first(n), last(n);

	int j = 0;
	for (int i = 0; i < s.size(), j < n; i++) {
		if (s[i] == t[j]) { first[j] = i; j++; }
	}

	j = n - 1;;
	for (int i = s.size() - 1; i >= 0, j>=0; i--) {
		if (s[i] == t[j]) { last[j] = i; j--; }
	}

	int res = 0;
	for (int i = 0; i < n; i++) {	
		int a = last[i] - first[i];
		int c1 = (i == 0) ? first[i] : (first[i] - first[i - 1] - 1);
		int c2 = (i == n - 1) ? (s.size() - last[i] - 1) : (last[i + 1] - last[i] - 1);

		res = max(res, c1 + a);
		res = max(res, c2 + a);
	}

	cout << res << endl;
}