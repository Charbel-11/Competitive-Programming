#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		string a; cin >> a;
		if (a.size() == 1) { cout << a << endl; continue; }
		int l = 0; bool o = ((a[0]-'0') % 2);
		for (int i = 1; i < a.size(); i++) {
			int cur = a[i] - '0';
			int firstL = a[l] - '0';

			if ((cur % 2 && !o) || (cur%2==0 && o)) {
				while (l != i) {
					if (cur < firstL) {
						cout << cur; a[i] = '.'; 
						break;
					}
					else { 
						cout << a[l]; 
						l++; while (a[l] == '.') { l++; }
						firstL = a[l] - '0';
					}
				}
				if (a[i] != '.' && l == i) { o = !o; }
			}
		}
		while (l < a.size()) {
			if (a[l] != '.') { cout << a[l]; }
			l++;
		}

		cout << endl;
	}
}