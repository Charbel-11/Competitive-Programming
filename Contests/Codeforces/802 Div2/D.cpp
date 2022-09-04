#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    vector<ll> v(n); for(auto &x : v){ cin >> x; }
    vector<ll> timeNeededGivenLocks(n);

    ll S = 0, sufSum = 0, prefSum = 0;
    for(auto &x : v){ S += x; sufSum += x; }

    ll timeNeededForPrevPref = 0;
    for(int i = 0; i < n; i++){
        ll timeNeededForPref = timeNeededForPrevPref;
        if (i == 0){ timeNeededForPref = v[i]; }
        else {
            ll extraAvailable = i * timeNeededForPrevPref - prefSum;
            ll left = v[i] - timeNeededForPrevPref - extraAvailable;
            if (left > 0) {
                timeNeededForPref += (left + i) / (i+1);
            }
        }
        timeNeededForPrevPref = timeNeededForPref;

        sufSum -= v[i]; prefSum += v[i];
        ll extraAvailable = (i+1) * timeNeededForPref - prefSum;
        ll extraTimeNeeded = 0;
        if (sufSum > extraAvailable){
            ll rem = sufSum - extraAvailable;
            extraTimeNeeded = (rem + i) / (i+1);
        }

        timeNeededGivenLocks[i] =  timeNeededForPref + extraTimeNeeded;
    }

    int q; cin >> q;
    while(q--){
        ll t; cin >> t;
        if (t < timeNeededGivenLocks[n-1]){ cout << -1 << '\n'; continue; }
        int l = 0, r = n-1;
        while (l < r){
            int mid = (l+r)/2;
            if (timeNeededGivenLocks[mid] <= t){ r = mid; }
            else{ l = mid + 1; }
        }
        cout << l + 1 << '\n';
    }
}