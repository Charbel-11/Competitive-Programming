#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int q;
	cin >> q;

	for (int i = 0; i < q; i++) {
		int b, w;
		cin >> b >> w;

		int c = min(w, b);
		int d = abs(w - b);

		if (d > c * 2 + 1) { cout << "NO" << endl; continue; }
		
		cout << "YES" << endl;
		int x = 3;
		c *= 2;

		while (c > 0) {
			cout << x << " " << 3 << endl;
			x++;
			c--;
		}

		if (w > b) {
			cout << x << " " << 3 << endl;
			d--;

			for (int i = 4; i <= x && d > 0; i += 2) {		//y = 2 here
				cout << i << " " << 2 << endl;
				d--;
			}
			for (int i = 4; i <= x && d > 0; i += 2) {		//y = 4 here
				cout << i << " " << 4 << endl;
				d--;
			}
		}
		else if (b > w) {
			cout << "2 3" << endl;
			d--;

			for (int i = 3; i < x && d > 0; i += 2) {		//y = 2 here
				cout << i << " " << 2 << endl;
				d--;
			}
			for (int i = 3; i < x && d > 0; i += 2) {		//y = 4 here
				cout << i << " " << 4 << endl;
				d--;
			}
		}
	}
}