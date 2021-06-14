#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

int main() {
	int n; cin >> n;
	vector<int> p(n);

	int even = n / 2, odd = n - n / 2;

	for (auto &x : p) {
		cin >> x;
		if (x == 0)continue;
		if (x % 2) {
			x = 1; odd--;
		}
		else {
			x = 2; even--;
		}
	}

	if (n == 1) { cout << 0 << endl; return 0; }

	if (p[0] == 0) {
		int i = 1;
		while (i < n && p[i] == 0) { i++; }
		if (i == n) { cout << 1 << endl; return 0; }
	}

	int res = 0;

	multimap<int, pair<int, int>> mE;
	int stateEven = 0, firstI = 0;
	for (int i = 0; i < n; i++) {
		if (p[i] == 2) {
			if (stateEven == 0) { stateEven = 1; firstI = i; continue; }
			if (stateEven == 1) {
				if (i != firstI + 1) {
					mE.insert({ i - firstI - 1, {firstI + 1, i - 1} });
				}
				firstI = i;
			}
		}
		else if (p[i] == 1) {
			stateEven = 0;
		}
	}

	for (auto it = mE.begin(); it != mE.end(); it++) {
		if (it->first <= even) {
			for (int i = it->second.first; i <= it->second.second; i++) {
				p[i] = 2; even--;
			}
		}
		else { break; }
	}

	multimap<int, pair<int, int>> mO;
	int stateOdd = 0; firstI = 0;
	for (int i = 0; i < n; i++) {
		if (p[i] == 1) {
			if (stateOdd == 0) { stateOdd = 1; firstI = i; continue; }
			if (stateOdd == 1) {
				if (i != firstI + 1) mO.insert({ i - firstI - 1, {firstI + 1, i - 1} });
				firstI = i;
			}
		}
		else if (p[i] == 2) {
			stateOdd = 0;
		}
	}

	for (auto it = mO.begin(); it != mO.end(); it++) {
		if (it->first <= odd) {
			for (int i = it->second.first; i <= it->second.second; i++) {
				p[i] = 1; odd--;
			}
		}
		else { break; }
	}

	if (p[0] == 0) {
		int i = 1;
		while (i < n && p[i] == 0) { i++; }
		bool ev = p[i] == 2;
		if (ev && even >= i) {
			for (int j = 0; j < i; j++) {
				p[j] = 2; even--;
			}
		}
		else if (!ev && odd >= i) {
			for (int j = 0; j < i; j++) {
				p[j] = 1; odd--;
			}
		}
	}

	if (p[n - 1] == 0) {
		int i = n - 2;
		while (i >= 0 && p[i] == 0) { i--; }
		bool ev = p[i] == 2;
		if (ev && even >= (n - i - 1)) {
			for (int j = n - 1; j > i; j--) {
				p[j] = 2; even--;
			}
		}
		else if (!ev && odd >= (n - i - 1)) {
			for (int j = n - 1; j > i; j--) {
				p[j] = 1; odd--;
			}
		}
	}

	if (p[0] == 0) {
		int i = 1;
		while (i < n && p[i] == 0) { i++; }
		bool ev = p[i] == 2;
		for (int j = i - 1; j >= 0; j--) {
			if (ev) {
				if (even) {
					p[j] = 2; even--;
				}
				else {
					p[j] = 1; odd--;
				}
			}
			else {
				if (odd) {
					p[j] = 1; odd--;
				}
				else {
					p[j] = 2; even--;
				}
			}
		}
	}

	for (int i = 1; i < n; i++) {
		if (p[i] == 0) {
			bool ev = p[i - 1] == 2;
			if (ev) {
				if (even) {
					p[i] = 2; even--;
				}
				else {
					p[i] = 1; odd--;
				}
			}
			else {
				if (odd) {
					p[i] = 1; odd--;
				}
				else {
					p[i] = 2; even--;
				}
			}
		}
	}

	for (int i = 0; i < n - 1; i++) {
		if (p[i] != p[i + 1])res++;
	}
	cout << res << endl;
}