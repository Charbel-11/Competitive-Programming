#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		string s; cin >> s;
		string a = "", b = "";
		bool oneSeen = false;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '2') { 
				if (!oneSeen) {
					a.push_back('1'); b.push_back('1');
				}
				else {
					a.push_back('0'); b.push_back('2');
				}
			}
			else if (s[i]=='1'){
				if (!oneSeen) {
					a.push_back('1'); b.push_back('0');
					oneSeen = true;
				}
				else {
					a.push_back('0'); b.push_back('1');
				}
			}
			else { a.push_back('0'); b.push_back('0'); }
		}
		cout << a <<endl<< b << endl;
	}
}