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

	string s; cin >> s; s += s;
	int n = s.size();
	
	int ans = 0, i = 0, k = 0;
	while (i < n/2) {
		ans = i; k = i;
		int j = i + 1;	//i+j-k represents a candidate substring start lex smaller than the one smaller than i
		//i is a better start than evrhtg between i and j-k
		for (; j < n && s[j] >= s[k]; j++) {
			if (s[j] == s[k]) { k++; }
			else if (s[j] > s[k]) { k = i; }
		}
		while (i <= k) { i += (j - k); }
	}

	cout << s.substr(ans, n/2) << '\n';
}