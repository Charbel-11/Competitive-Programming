#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		string a, b; cin >> a >> b;
        int n = a.size();

        bool OK = false;
        for(int i = 1; i < a.size(); i++){
            if (a[i] == '1' && a[i-1] == '0' && b[i] == '1' && b[i-1] == '0') {
                OK = true;
                break;
            }
        }

        if (OK){ cout << "YES\n"; }
        else{ cout << "NO\n"; }
	}
}