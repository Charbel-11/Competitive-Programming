#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		string t; cin >> t;
		if (t.length() <= 2) { cout << t << endl; continue; }
		bool equ = true;
		for (int i = 1; i < t.length(); i++) {
			if (t[i] != t[i - 1]) { equ = false; break; }
		}
		if (equ) { cout << t << endl; continue; }

		string s = ""; s.push_back(t[0]);
		for (int i = 1; i < t.length(); i++) {
			if (t[i]==t[i-1]){
				s.push_back((t[i] == '1' ? '0' : '1'));
				s.push_back(t[i]);
			}
			else {
				s.push_back(t[i]);
			}
		}
		cout << s << endl;
	}
}