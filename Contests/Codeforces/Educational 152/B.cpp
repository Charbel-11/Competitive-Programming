#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n, k; cin >> n >> k;
        vector<int> a(n); for(auto &x : a){ cin >> x; x %= k; if (x==0){ x+= k; } }

        vector<pair<int, int>> monsts(n);
        for(int i = 0; i < n; i++){ monsts[i] = {a[i], i}; }
        sort(monsts.rbegin(), monsts.rend());

        int l = 0;
        for(int i = 1; i < n; i++){
            if (monsts[i].first != monsts[i-1].first){
                sort(monsts.begin()+l, monsts.begin()+i);
                l = i;
            }
        }
        sort(monsts.begin()+l, monsts.begin()+n);

        for(int i = 0; i < n; i++){
            cout << monsts[i].second + 1 << ' ';
        }
        cout << '\n';
	}
}