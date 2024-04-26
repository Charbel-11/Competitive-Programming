#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

    ll n; cin >> n;
    string s; cin >> s;
    ll pos = 0, neg = 0;
    for(auto &c : s){
        pos += c == '+';
        neg += c == '-';
    }

	int t; cin >> t;
	while(t--){
        ll a, b; cin >> a >> b;
        if (a < b){ swap(a, b); }
        ll ma = a * pos - b * neg;
        ll diff = a-b;

        if (diff == 0){
            if (ma == 0) { cout << "YES\n"; }
            else { cout << "NO\n"; }
        }
        else {
            if (ma >= 0 && ma % diff == 0 && ma / diff <= n) { cout << "YES\n"; }
            else { cout << "NO\n"; }
        }
	}
}