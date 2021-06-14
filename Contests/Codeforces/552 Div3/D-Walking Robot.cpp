#include <iostream>
#include <string>
#include <vector>

using namespace std;


int main() {
	int n, b, a;
	cin >> n >> b >> a;

	vector<int> sun(n);
	for (int i = 0; i < n; i++) {
		cin >> sun[i];
	}

	int maxCap = a;
	int maxSeg = 0;
	for (int i = 0; i < n; i++) {
		if (a == 0 && b == 0) { break; }
	
		maxSeg++;
		if (sun[i] == 0) {
			if (a != 0) {
				a--;
				continue;
			}
			b--;
		}
		else {
			if (a < maxCap) {
				if (b != 0) {
					b--;
					a++;
					continue;
				}
				a--;
			}
			else {
				if (a != 0) {
					a--;
					continue;
				}
				b--;
			}
		}
	}

	cout << maxSeg << endl;
}