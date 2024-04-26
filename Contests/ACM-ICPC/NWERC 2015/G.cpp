#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct FT {
    int n; vector<int> vals; FT() {};
    FT(int n, bool b = false) : n(n) { vals.resize(n + 1, b); }

    void update(int i, int x) {
        for (++i; i <= n; i += i & -i) { vals[i] += x; }
    }

    int query(int i) const { // sum from 0 ... i assert(i >= -1 && i < n);
        int sum = 0;
        for (++i; i; i -= i & -i) { sum += vals[i]; }
        return sum;
    }
    int query(int l, int r) { return query(r) - query(l - 1); }
};

ll countDisagreements(vector<int>& a, vector<int>& b){
    int n = a.size();
    vector<int> idx2(n);
    for(int i = 0; i < n; i++){
        idx2[b[i]] = i;
    }

    FT ft(n); ll disag = 0;
    for(int i = 0; i < n; i++){
        disag += ft.query(idx2[a[i]], n - 1);
        ft.update(idx2[a[i]], 1);
    }
    return disag;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int n; cin >> n;
    vector<int> a1(n); for(auto &x : a1){ cin >> x; x--; }
    vector<int> a2(n); for(auto &x : a2){ cin >> x; x--; }
    vector<int> a3(n); for(auto &x : a3){ cin >> x; x--; }

    ll disagreements = countDisagreements(a1, a2) + countDisagreements(a1, a3) + countDisagreements(a2, a3);
    ll ans = (ll)n*(n-1)/2 - disagreements / 2;
    cout << ans << '\n';
}