#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool isPrime(int n) {
    for(int i = 2; i*i <= n; i++){
        if (n % i == 0){ return false; }
    }
    return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		string s; cin >> s; int res = -1;
        for(int i = 0; i < 9; i++){
            for(int j = i + 1; j < 9; j++){
                int cur = 10*(s[i]-'0') + (s[j]-'0');
                if (isPrime(cur)){ res = cur; break; }
            }
            if (res != -1){ break; }
        }

        cout << res << '\n';
	}
}