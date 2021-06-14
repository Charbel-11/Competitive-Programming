#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;

	int m = (n + 2) / 2;

	cout << m << endl;

	for (int i = 0; i < m; i++) {
		cout << i+1 << " " << 1 << endl;
		n -= 1;
	}
	
	for (int i = m - n; i < m; i++) {
		cout << i + 1 << " " << m << endl;
	}
}