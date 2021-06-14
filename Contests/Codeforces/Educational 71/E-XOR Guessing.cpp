#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>

using namespace std;
vector<int> pow2;
int limit;
set<int> nums;

void printAll(int i, vector<bool> mask) {
	int res = 0;
	for (int j = 13; j >= 0; j--) {
		if (mask[j] == 1) { res += (1 << (13 - j)); }
	}
	if (res != 0) { nums.insert(res); }

	if (i == limit) { return; }
	printAll(i - 1, mask);
	mask[i - 1] = 1;
	printAll(i - 1, mask);
}

int main() {
	pow2.resize(14, 1);
	for (int i = 1; i < 14; i++) { pow2[i] = 2 * pow2[i - 1]; }

	limit = 0;
	vector<bool> mask = { 0,0,0,0,0,0,1,0,0,0,0,0,0,0 };
	cout << "? "; printAll(7, mask);
	vector<bool> mask2 = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	printAll(7, mask2);
	int count = 0;
	for (auto x : nums) {
		cout << x << " "; count++;
		if (count == 100) { break; }
	}
	fflush(stdout);

	int n1; cin >> n1;

	nums.clear();
	limit = 7;
	mask = { 0,0,0,0,0,0,0,0,0,0,0,0,0,1 };
	cout << "? "; printAll(13, mask);
	mask2 = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	printAll(13, mask2);
	count = 0;
	for (auto x : nums) {
		cout << x << " "; count++;
		if (count == 100) { break; }
	}
	fflush(stdout);

	int n2; cin >> n2;

	int res = n1 % pow2[7] + (n2 - n2 % pow2[7]);

	cout << "! " << res << endl;
}

/*#include <iostream>
using namespace std;

int a[100];

int main() {
	for (int i = 0; i < 100; i++) { a[i] = i + 1; }
	cout << "? "; fflush(stdout);
	for (int i = 0; i < 100; i++) { cout << a[i] << ' '; fflush(stdout); a[i] <<= 7; }
	cout << endl; int x; cin >> x;
	cout << "? "; fflush(stdout);
	for (int i = 0; i < 100; i++) { cout << a[i] << ' '; fflush(stdout); }
	cout << endl; int y; cin >> y;
	cout << "! " << ((x >> 7) << 7) + y % 128 << endl; fflush(stdout);
	cin.ignore(2); return 0;
}*/