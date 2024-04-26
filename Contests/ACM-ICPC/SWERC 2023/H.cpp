#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
        vector<int> a(n); for(auto &x : a){ cin >> x; x--; }
        vector<int> b(n); for(auto &x : b){ cin >> x; x--; }

        vector<bool> seen(n, 0);
        int r = -1;
        int i = n-1, j = n-1;
        while(i >= 0 && j >= 0){
            while(seen[b[j]] && j >= 0){ r = max(r, j); j--; }
            if (j < 0){ break; }
            while(a[i] != b[j]){
                seen[a[i]] = true;
                i--;
            }
            i--; j--;
        }

        while(j >= 0){
            if (seen[b[j]]){ r = max(r, j); }
            j--;
        }

        cout << r + 1 << '\n';
	}
}