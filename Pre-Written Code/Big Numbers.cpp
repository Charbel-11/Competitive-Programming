#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

//assumes a>b
string subtract(string a, string b) {
	if (a == b) { return "0"; }
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	while (a.size() < b.size()) { a.push_back('0'); }
	while (b.size() < a.size()) { b.push_back('0'); }

	int n = (int)a.size(), carry = 0; string res;
	for (int i = 0; i < n; i++) {
		int x = (a[i] - '0') - (b[i] - '0') - carry;
		if (x >= 0) { res.push_back(x + '0'); carry = 0; }
		else { res.push_back(x + 10 + '0'); carry = 1; }
	}
	while (res.back() == '0') { res.pop_back(); }
	reverse(res.begin(), res.end());
	return move(res);
}

string add(string a, string b) {
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	while (a.size() < b.size()) { a.push_back('0'); }
	while (b.size() < a.size()) { b.push_back('0'); }

	int n = (int)a.size(), carry = 0; string res = "";
	for (int i = 0; i < n; i++) {
		int x = (a[i] - '0') + (b[i] - '0') + carry;
		if (x < 10) { res.push_back(x + '0'); carry = 0; }
		else { res.push_back(x - 10 + '0'); carry = 1; }
	}
	if (carry == 1) { res.push_back('1'); }
	while (!res.empty() && res.back() == '0') { res.pop_back(); }
	reverse(res.begin(), res.end());
	if (res.empty()) { res = "0"; }
	return move(res);
}

bool compareStrings(const string &a, const string &b) {
	if (a.size() != b.size()) { return a.size() < b.size(); }
	return a < b;
}