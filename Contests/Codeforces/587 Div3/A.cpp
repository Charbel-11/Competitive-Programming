#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int n; cin >> n;
	string s; cin >> s;
	int a = 0, b = 0;
	int res = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == 'a') { a++; }
		else { b++; }
		if ((i + 1) % 2 == 0) {
			if (a > b) {
				int t = (a - b) / 2;
				res += t;
				int j = i;
				while (b != a) {
					if (s[j] == 'a') {
						s[j] = 'b';
						a--; b++;
					}
					j--;
				}
			}
			else if (b > a) {
				int t = (b - a) / 2;
				res += t;
				int j = i;
				while (b != a) {
					if (s[j] == 'b') {
						s[j] = 'a';
						a++; b--;
					}
					j--;
				}
			}
		}
	}

	cout << res << endl;
	for (int i = 0; i < n; i++) {
		cout << s[i];
	}cout << endl;
}