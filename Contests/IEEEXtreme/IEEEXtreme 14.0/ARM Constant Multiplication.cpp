#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		unsigned int C; cin >> C;

		if (C == 0) { cout << "MOV R0, R0, LSR #32\n"; cout << "END\n"; continue; }
		if (C == 1) { cout << "END\n"; continue; }

		int shift = 0;
		while (C) {
			if (C % 2) {
				bool last = (C / 2 == 0);
				if (last) {
					cout << "ADD R0, R1, R0, LSL #" << shift << '\n';
				}
				else {
					cout << "ADD R1, R1, R0, LSL #" << shift << '\n';
				}
			}
			C /= 2; shift++;
		}

		cout << "END\n";
	}
}