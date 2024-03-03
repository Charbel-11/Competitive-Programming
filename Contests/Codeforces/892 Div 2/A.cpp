#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
        vector<int> a(n);
        for(auto &x : a){ cin >> x; }
        sort(a.begin(), a.end());

        vector<int> c;
        c.push_back(a[n-1]); a.pop_back();
        while(!a.empty() && a.back() == c.back()){
            c.push_back(a.back()); a.pop_back();
        }

        if (a.empty()){ cout << -1 << '\n'; }
        else{
            cout << a.size() << " " << c.size() << '\n';
            for(auto &x : a){ cout << x << ' '; } cout << '\n';
            for(auto &x : c){ cout << x << ' '; } cout << '\n';
        }
	}
}