#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, k; cin >> n >> k;
    vector<int> a(n); for(auto &x : a){ cin >> x;}

    int ans = -1;
    if (a[n-1] < a[n-2]){
        a.push_back(max(0, a[n-1] * 2 - a[n-2])); n++;
        while(a.back() >= k){
            a.push_back(max(0, a[n-1] * 2 - a[n-2])); n++;
        }
        ans = n;
    }

    if (ans == -1){
        cout << "Python will never be faster than C++\n";
    }
    else{
        cout << "Python 3." << ans << " will be faster than C++\n";
    }
}