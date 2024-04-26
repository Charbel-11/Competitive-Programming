#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	double n, w, u, v, t1, t2;
    cin >> n >> w >> u >> v >> t1 >> t2;
    t2 -= t1;

    double timePerLane = w/v; t2 += timePerLane;
    multimap<double, bool> ships; ships.insert({t2*u, true});
    for(int i = 0; i < n; i++){
        char c; cin >> c;
        int m; cin >> m;

        double laneShift = timePerLane * i * u;
        while(m--){
            double l, p; cin >> l >> p;
            if (c == 'E') { p *= -1; }

            p -= t1 * u; p -= laneShift;
            double start = p, end = p+l;
            start = max(start, 0.0);
            end = min(end, t2 * u);
            if (end <= 0 || end < start){ continue; }

            ships.insert({start, true});
            ships.insert({end, false});
        }
    }

    double ans = 0, lastEnd = 0; int curCnt = 0;
    for(auto [loc, start] : ships){
        if(start){
            if (curCnt == 0){
                ans = max(ans, (loc - lastEnd)/u - timePerLane);
            }
            curCnt++;
        }
        else{ curCnt--; lastEnd = loc; }
    }

    cout << setprecision(6) << fixed << ans << '\n';
}

