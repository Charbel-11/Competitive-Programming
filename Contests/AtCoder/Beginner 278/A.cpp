#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, k; cin >> n >> k;
    vector<int> A(n); for(auto &x : A){ cin >> x;}

    k = min(k, n);
    vector<int> ans;
    for(int i = k; i < n; i++){ ans.push_back(A[i]); }
    for(int i = 0; i < k; i++){ ans.push_back(0); }

    for(auto &x : ans){ cout << x << ' '; }
}