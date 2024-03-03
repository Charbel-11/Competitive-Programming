#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
        vector<int> a(n); for(auto &x : a){ cin >> x; }
        if (a[0] != n){ cout << "NO\n"; continue; }

        int len = 1, idx = 0;
        vector<int> b(n, 0);
        for(int i = 1; i < n; i++, len++){
            if (a[i] == a[i-1]){ continue; }
            for(int j = a[i]; j < a[i-1]; j++){ b[idx++] = len; }
        }
        for(int j = 0; j < a[n-1]; j++){ b[idx++] = len; }

        bool OK = true;
        reverse(b.begin(), b.end());
        for(int i = 0; i < n; i++){
            if (a[i] != b[i]){ OK = false; break; }
        }

        if (OK) { cout << "YES\n"; }
        else { cout << "NO\n"; }
	}
}