#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int n, m, k; cin >> n >> m >> k;
	
	if (n == 1) {
		string s(m - 1, 'R'), s2(m - 1, 'L');
		cout << s.size() + s2.size() << endl;
		cout << s << s2 << endl;
		return 0;
	}
	if (m == 1) {
		string s(n - 1, 'D'), s2(n - 1, 'U');
		cout << s.size() + s2.size() << endl;
		cout << s << s2 << endl;
		return 0;
	}

	string res;
	string s(m - 1, 'L'), s2(n - 1, 'U');
	res = s + s2;
	bool alt = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < m; j++) {
			if (alt) { res.push_back('R'); }
			else { res.push_back('L'); }
		}
		alt = !alt;
		if (i!=n)res.push_back('D');
	}
	cout << res.size() << endl << res << endl;
}