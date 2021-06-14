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
		string s; cin >> s;
		int x = 0;
		bool OK = true;
		for(int i = 0; i < s.size(); i++){
			if (s[i] == '(' && i == s.size()-1) { 
				OK = false;
			}
			else if (s[i] == ')' && !i) { 
				OK = false;
			}
			else { x++; }
		}
		if (x % 2) { OK = false; }
		cout << (OK ? "YES" : "NO") << '\n';
	}
}