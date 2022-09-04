#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int k; cin >> k;
	cout << (21 + k / 60) << ":";
	if ((k % 60) < 10) { cout << "0"; }
	cout << (k % 60) << '\n';
}
