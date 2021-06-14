#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
	int n; cin >> n;
	string s; cin >> s;

	int A, B, C; A = B = C = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == 'A') { A++; }
		else if (s[i] == 'B') { B++; }
		else if (s[i] == 'C') { C++; }
	}

	int res = INT_MAX;
	char letters[3] = { 'A', 'B', 'C' };
	int letterFreq[3] = { A, B, C };

	for (int z = 0; z < 2; z++) {
		int tA, t1; int dif = 0;
		if (letters[1] == 'B') { tA = A; t1 = B; }
		else { tA = A; t1 = C; }
		int i = 0;
		while (i < tA) {
			if (s[i] != letters[0]) { dif++; }
			i++;
		}
		while (i < tA + t1) {
			if (s[i] != letters[1]) { dif++; }
			i++;
		}
		while (i < n) {
			if (s[i] != letters[2]) { dif++; }
			i++;
		}
		res = min(res, dif);
		if (res == 0) { cout << 0 << endl; return 0; }

		int iA, i1, i2;
		if (letters[1] == 'B') {
			iA = 1; i1 = A + 1;  i2 = A + B + 1;
			if (B == 0) { i1 = i2; letters[1] = 'C'; }
			if (C == 0) { i2 = iA; letters[2] = 'A'; }
		}
		else {
			iA = 1; i1 = A + 1; i2 = A + C + 1;
			if (B == 0) { i2 = iA; letters[2] = 'A'; }
			if (C == 0) { i1 = i2; letters[1] = 'B'; }
		}
		if (A == 0) { iA = i1; letters[0] = letters[1]; }

		int rot = 1;
		while (rot != n) {
			if (iA == n) { iA = 0; }
			if (i1 == n) { i1 = 0; }
			if (i2 == n) { i2 = 0; }

			int newA = i1 - 1, new1 = i2 - 1, new2 = iA - 1;
			if (newA == n) { newA = 0; } if (newA == -1) { newA = n - 1; }
			if (new1 == n) { new1 = 0; } if (new1 == -1) { new1 = n - 1; }
			if (new2 == n) { new2 = 0; } if (new2 == -1) { new2 = n - 1; }

			if (letterFreq[0]) {
				if (s[newA] == letters[0]) { dif--; }
				else if (s[newA] == letters[1]) { dif++; }
			}
			if (letterFreq[1]) {
				if (s[new1] == letters[1]) { dif--; }
				else if (s[new1] == letters[2]) { dif++; }
			}
			if (letterFreq[2]) {
				if (s[new2] == letters[2]) { dif--; }
				else if (s[new2] == letters[0]) { dif++; }
			}

			res = min(res, dif);

			iA++; i1++; i2++; rot++;
		}

		letters[1] = 'C'; letters[2] = 'B';
		letterFreq[1] = C; letterFreq[2] = B;
	}
	cout << res << endl;
}