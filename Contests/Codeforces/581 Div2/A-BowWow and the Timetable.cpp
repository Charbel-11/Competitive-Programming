#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	string s; cin >> s; 
	int n; n = s.size();

	if (s[0] == '0') { cout << 0 << endl; return 0; }

	int res = 0; int b = false; bool odd = false;
	for (int i = 0; i < n; i++) {
		if (s[i] == '1') { 
			res = (n - 1 - i) / 2; res++;
			if ((n - 1 - i) % 2) { odd = true; }
			i++;
			
			while (i < n) { 
				if (s[i] == '1') { b = true; break; } 
				i++; 
			}
			break;
		}
	}
	if (!b && !odd) res--;
	
	cout << res << endl;
}