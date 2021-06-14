#include <string>
#include <iostream>

using namespace std;

int main() {
	int T; cin >> T;
	for (int z = 0; z < T; z++) {
		int a, b; cin >> a >> b;
		if (a == b) { cout << "YES" << endl; }
		else { cout << "NO" << endl; }
	}
}