#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int a, b; cin >> a >> b;
	
	if (a == b) {
		string s1 = to_string(a); s1.push_back('1');
		string s2 = to_string(b); s2.push_back('2');
		cout << s1 << " " << s2 << endl;
	}
	else if (a==b-1){
		string s1 = to_string(a); s1.push_back('9');
		string s2 = to_string(b); s2.push_back('0');
		cout << s1 << " " << s2 << endl;
	}
	else if (a == 9 && b == 1) {
		cout << 9 << " " << 10 << endl;
	}
	else {
		cout << -1 << endl;
	}
}