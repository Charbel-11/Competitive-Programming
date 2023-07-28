#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> a(n);
        vector<pair<int, int>> sortedA;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            sortedA.emplace_back(a[i], i);
        }
        sort(sortedA.begin(), sortedA.end());

        int curN = n;
        bool OK = true;
        int l = 0, r = n - 1, add = 0;
        vector<int> b(n);
        while (l <= r) {
            if (sortedA[r].first + add == curN) {
                if (sortedA[l].first + add == 0) {
                    OK = false;
                    break;
                }
                b[sortedA[r].second] = curN;
                add--;
                r--;
            } else {
                if (sortedA[l].first + add == 0) {
                    b[sortedA[l].second] = -curN;
                    l++;
                }
                else{
                    OK = false;
                    break;
                }
            }
            curN--;
        }

        if (!OK) { cout << "NO\n"; }
        else {
            cout << "YES\n";
            for (auto &x: b) { cout << x << ' '; }
            cout << '\n';
        }
    }
}