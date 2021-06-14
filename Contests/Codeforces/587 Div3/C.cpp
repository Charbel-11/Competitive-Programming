#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int x1, x2, y1, y2; cin >> x1 >> y1 >> x2 >> y2;
	int x3, x4, y3, y4; cin >> x3 >> y3 >> x4 >> y4;
	int x5, x6, y5, y6; cin >> x5 >> y5 >> x6 >> y6;

	if (x5 <= x1 && x1 <= x6) {
		if (x6 >= x2) {
			if (y1 >= y5 && y6 >= y2) {
				cout << "NO" << endl; return 0;
			}
			else if (y1 >= y5) {
				y1 = y6;
			}
			else if (y6 >= y2) {
				y2 = y5;
			}
			else if (y5 >= y1 && y6 <= y2){
				if (x3 <= x1 && x4 >= x2 && y3 <= y1 && y4 >= y2) {
					cout << "NO" << endl; return 0;
				}
			}
		}
		else {
			if (y1 >= y5 && y2 <= y6) {
				x1 = x6;
			}
			else {
				if (x3 <= x1 && x4 >= x2 && y3 <= y1 && y4 >= y2) {
					cout << "NO" << endl; return 0;
				}
			}
		}
	}
	else if (x5 > x1 && x5 <= x2) {
		if (y1 >= y5 && y2 <= y6) {
			x2 = x5;
		}
		else {
			if (x3 <= x1 && x4 >= x2 && y3 <= y1 && y4 >= y2) {
				cout << "NO" << endl; return 0;
			}
		}
	}

	if (x3 <= x1 && x1 <= x4) {
		if (x4 >= x2) {
			if (y1 >= y3 && y4 >= y2) {
				cout << "NO" << endl; return 0;
			}
			else if (y1 >= y3) {
				y1 = y4;
			}
			else if (y4 >= y2) {
				y2 = y3;
			}
			else if (y3 >= y1 && y4 <= y2) {
				if (x5 <= x1 && x6 >= x2 && y5 <= y1 && y6 >= y2) {
					cout << "NO" << endl; return 0;
				}
			}
		}
		else {
			if (y1 >= y3 && y2 <= y4) {
				x1 = x4;
			}
			else {
				if (x5 <= x1 && x6 >= x2 && y5 <= y1 && y6 >= y2) {
					cout << "NO" << endl; return 0;
				}
			}
		}
	}
	else if (x3 > x1 && x3 <= x2) {
		if (y1 >= y3 && y2 <= y4) {
			x2 = x3;
		}
		else {
			if (x5 <= x1 && x6 >= x2 && y5 <= y1 && y6 >= y2) {
				cout << "NO" << endl; return 0;
			}
		}
	}

	cout << "YES" << endl;
}