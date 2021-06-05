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

//If even is true, res[i] = length/2 of the even palindrome with right center at i
//If even is false, res[i] = (length-1)/2 of the odd palindrome with center at i
//For example, "aaaa" even returns: 0 1 2 1, odd: 0 1 1 0
vector<int> manacher(string& s, bool even) {
	int n = s.size();
	vector<int> res(n);
	int l = 0, r = -1;
	for (int i = 0; i < n; i++) {
		int k;
		if (i > r) { k = 1; }
		else { k = min(res[l + r - i + even], r - i + even) + 1; }
		while (i + k - even < n && i - k >= 0 && s[i + k - even] == s[i - k]) { k++; }
		res[i] = --k;
		if (i + k - even > r) {
			l = i - k;
			r = i + k - even;
		}
	}
	return move(res);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	string s; cin >> s; int n = s.size();
	vector<int> oddP = manacher(s, false), evenP = manacher(s, true);

	int idx = -1, maxLen = 0;
	for (int i = 0; i < n; i++) {
		int lenOdd = oddP[i] * 2 + 1;
		if (lenOdd > maxLen) { maxLen = lenOdd; idx = i - oddP[i]; }
		int lenEven = evenP[i] * 2;
		if (lenEven > maxLen) { maxLen = lenEven; idx = i - evenP[i]; }
	}

	for (int i = idx; i < idx + maxLen; i++) {
		cout << s[i];
	}
	cout << '\n';
}