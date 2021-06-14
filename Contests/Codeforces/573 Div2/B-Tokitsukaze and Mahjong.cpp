#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	string s1,s2,s3;
	cin >> s1 >> s2 >> s3;

	char c1 = s1[1];
	char c2 = s2[1];
	char c3 = s3[1];
	int n1 = s1[0] - '0';
	int n2 = s2[0] - '0';
	int n3 = s3[0] - '0';
	vector<int> temp(3);
	temp[0] = n1;
	temp[1] = n2;
	temp[2] = n3;
	sort(temp.begin(), temp.end());

	if (c1 == c2 && c2 == c3) {
		if (n1 == n2 && n2 == n3) {
			cout << 0 << endl;
			return 0;
		}
		if (temp[0] == temp[1] - 1 && temp[1] == temp[2] - 1) {
			cout << 0 << endl;
			return 0;
		}

		if (temp[0] == temp[1] - 1 || temp[1] == temp[2] - 1 || temp[0]==temp[1] || temp[1] == temp[2]) {
			cout << 1 << endl;
			return 0;
		}
		if (temp[0] == temp[1] - 2 || temp[1] == temp[2] - 2) {
			cout << 1 << endl;
			return 0;
		}

		cout << 2 << endl;
		return 0;
	}

	if (c1 == c2) {
		if (abs(n1-n2)<=2) {
			cout << 1 << endl;
			return 0;
		}
	}
	if (c2 == c3) {
		if (abs(n2 - n3) <= 2) {
			cout << 1 << endl;
			return 0;
		}
	}
	if (c1 == c3) {
		if (abs(n1 - n3) <= 2) {
			cout << 1 << endl;
			return 0;
		}
	}

	cout << 2 << endl;
	return 0;
}