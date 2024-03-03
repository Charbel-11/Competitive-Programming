#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    for(int i = 0; i < n; i++){
        for(int j = 1; j <= n; j++){
            int cur; cin >> cur;
            if (cur){ cout << j << ' '; }
        }
        cout << '\n';
    }
}

