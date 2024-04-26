#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		string s; cin >> s;
        if (s == "00:00"){
            cout << "12:00 AM\n";
            continue;
        }
        int num1 = (s[0] - '0') * 10 + (s[1] - '0');
        if (num1 == 0){ cout << "12:" << s[3] << s[4] << " AM\n"; }
        else if (num1 < 12){ cout << s << ' ' << "AM\n"; }
        else if (num1 == 12){ cout << s << ' ' << "PM\n"; }
        else{
            if (num1-12 < 10){ cout << "0" << num1-12; }
            else { cout << num1-12; }
            cout << ":" << s[3] << s[4] << " PM\n";
        }
	}
}

