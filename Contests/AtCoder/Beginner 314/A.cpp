#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string pi = "3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679";
    int n; cin >> n;
    n += 2;
    for(int i = 0; i < n; i++){ cout << pi[i]; }
    cout << '\n';
}