#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	int x,y,z;
	cin >> x >> y >> z;

	if (x < y) {
		if (x + z < y) {
			cout << "-" << endl;
			return 0;
		}
	}

	if (y < x) {
		if (y + z < x) {
			cout << "+" << endl;
			return 0;
		}
	}

	if (y == x && z == 0) {
		cout << "0" << endl;
		return 0;
	}

	cout << "?" << endl;
}