#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
	int q;
	cin >> q;

	for (int z = 0; z < q; z++) {
		int n;
		cin >> n;

		multimap<int, vector<int>> x;
		multimap<int, vector<int>> y;

		for (int i = 0; i < n; i++) {
			int cx, cy, f1, f2, f3, f4;
			cin >> cx >> cy >> f1 >> f2 >> f3 >> f4;

			vector<int> tempX = { f1, f3 };		//f1 go left, f3 go right
			x.insert({ cx, tempX });
			vector<int> tempY = { f2, f4 };		//f2 go top, f4 go bot
			y.insert({ cy, tempY });
		}

		int answX;
		int answY;
		bool OK = true;
		map<int, vector<int>>::iterator itrX = prev(x.end());
		while (itrX != x.begin()) {
			if (itrX->second[0] == 0) {
				answX = itrX->first;
				break;
			}

			itrX = prev(itrX);
		}
		if (itrX == x.begin()) { answX = itrX->first; }
		else {
			itrX = prev(itrX);
			while (itrX != x.begin()) {
				if (itrX->second[1] == 0 && itrX->first != answX) {
					OK = false;
					break;
				}

				itrX = prev(itrX);
			}
			if (itrX == x.begin() && itrX->second[1] == 0 && itrX->first != answX) { OK = false; }
		}

		if (!OK) { cout << 0 << endl; continue; }

		map<int, vector<int>>::iterator itrY = prev(y.end());
		while (itrY != y.begin()) {
			if (itrY->second[1] == 0) {
				answY = itrY->first;
				break;
			}

			itrY = prev(itrY);
		}
		if (itrY == y.begin()) { answY = itrY->first; }
		else {
			itrY = prev(itrY);
			while (itrY != y.begin()) {
				if (itrY->second[0] == 0 && itrY->first != answY) {
					OK = false;
					break;
				}

				itrY = prev(itrY);
			}
			if (itrY == y.begin() && itrY->second[0] == 0 && itrY->first != answY) { OK = false; }
		}

		if (!OK) { cout << 0 << endl; continue; }

		cout << 1 << " " << answX << " " << answY << endl;
	}
}