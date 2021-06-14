#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int T;
	cin >> T;

	for (int i = 0; i < T; i++) {
		string a, b;
		cin >> a >> b;
		int k = 0;

		int aI = a.size() - 1;
		int bI = b.size() - 1;

		while (aI >= 0 && bI >= 0) {
			if (a[aI] == '0') {
				if (b[bI] == '0') {
					aI--; bI--;
				}
				else {
					aI--; k++;
				}
			}
			else {
				if (b[bI] == '1') {
					break;
				}
				aI--;
				bI--;
			}
		}

		cout << k << endl;
	}
}