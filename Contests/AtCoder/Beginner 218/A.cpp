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

	int n; cin >> n;
	string s; cin >> s;

	if (s[n - 1] == 'o') { cout << "Yes" << '\n'; }
	else { cout << "No" << '\n'; }
}