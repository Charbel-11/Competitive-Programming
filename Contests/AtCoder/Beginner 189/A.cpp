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

	string s; cin >> s;
	if (s[0] == s[1] && s[1] == s[2]) { cout << "Won" << '\n'; }
	else { cout << "Lost" << '\n'; }
}