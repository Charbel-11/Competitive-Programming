#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	int T; cin >> T;

	for (int z = 0; z < T; z++) {
		ll str, intel, exp; cin >> str >> intel >> exp;

		if (str + exp <= intel) { cout << 0 << endl; continue; }
		if (exp == 0) { cout << 1 << endl; continue; }

		if (intel > str) {
			exp -= (intel - str); 
			ll res = (exp + 1) / 2;
			cout << res << endl;
		}
		else {
			str -= intel; intel = 0;
			str += exp;		
			ll res =  min(exp+1, (str+1)/2);
			cout << res << endl;
		}
	}
}