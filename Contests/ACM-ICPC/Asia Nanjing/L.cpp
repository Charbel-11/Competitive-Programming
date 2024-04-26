#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Parcel{
    ll number, weight, floor;
    Parcel(ll n, ll w, ll f):number(n), weight(w), floor(f){}

    bool operator <(const Parcel& rhs) const{
        return floor < rhs.floor;
    }
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		ll n, k; cin >> n >> k;
        vector<Parcel> parcels;
        for(int i = 0; i < n; i++){
            ll c, w, f; cin >> c >> w >> f;
            parcels.emplace_back(c, w, f);
        }

        sort(parcels.rbegin(), parcels.rend());
        int firstW1 = 0;
        while(firstW1 < n && parcels[firstW1].weight != 1){ firstW1++; }

        ll ans = 0, curK = k, curMaxFloor = -1;
        for(int i = 0; i < n; i++){
            while(firstW1 == i || (firstW1 < n && parcels[firstW1].weight != 1)){ firstW1++; }
            if (parcels[i].number == 0){ continue; }
            if (curMaxFloor == -1){ curMaxFloor = parcels[i].floor; }

            ll canTake = curK / parcels[i].weight;
            canTake = min(canTake, parcels[i].number);
            parcels[i].number -= canTake;
            curK -= parcels[i].weight * canTake;

            if (parcels[i].number == 0){ continue; }
            if (curK == 1 && firstW1 != n){
                parcels[firstW1].number--;
                if (parcels[firstW1].number == 0){
                    firstW1++;
                    while(firstW1 < n && parcels[firstW1].weight != 1){ firstW1++; }
                }
            }
            ans += curMaxFloor;
            curMaxFloor = parcels[i].floor;
            curK = k;

            // take full cycles
            ll numRepetitionsNeeded = parcels[i].number * parcels[i].weight / curK;
            ans += curMaxFloor * numRepetitionsNeeded;
            parcels[i].number -= numRepetitionsNeeded * curK / parcels[i].weight;

            curMaxFloor = -1; i--;
        }

        if (curK != k){ ans += curMaxFloor; }
        cout << ans << '\n';
	}
}

