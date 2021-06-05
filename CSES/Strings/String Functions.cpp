#include <string>
#include <iostream>
#include <vector>
using namespace std;

//For each i in the returned vector, the number represents the length of 
//the longest proper prefix equal to the suffix ending at index i, both in the substring s[0..i]
//Proper prefix means prefix != string
vector<int> prefixFunction(string& s) {
	vector<int> pf(s.size(), 0);
	for (int i = 1; i < s.size(); i++) {
		int j = pf[i - 1];
		while (j > 0 && s[j] != s[i]) { j = pf[j - 1]; }
		if (s[j] == s[i]) { j++; }
		pf[i] = j;
	}
	return move(pf);
}

vector<int> ZAlgo(string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    int L = 0, R = 0;
    for (int i = 1; i < n; i++) {
        if (i > R) {
            L = R = i;
            while (R < n && s[R - L] == s[R]) { R++; }
            z[i] = R - L; R--;
        }
        else {
            int k = i - L;
            if (z[k] < R - i + 1) { z[i] = z[k]; continue; }
            L = i;
            while (R < n && s[R - L] == s[R]) { R++; }
            z[i] = R - L; R--;
        }
    }
    return move(z);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string s; cin >> s;
	vector<int> kmp = prefixFunction(s);
    vector<int> z = ZAlgo(s);
	for (auto& x : z) { cout << x << ' '; } cout << '\n';
	for (auto& x : kmp) { cout << x << ' '; } cout << '\n';
}