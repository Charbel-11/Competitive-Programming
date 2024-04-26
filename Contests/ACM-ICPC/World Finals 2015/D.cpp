#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
const ld PI = acos(-1);

ld SphereVolume(ld R) {
    return (4.0 / 3.0) * PI * R * R * R;
}

ld GetSphericalSectorArea(ld L, ld O, ld R){
    ld x = abs(O - L), R2 = R * R, R3 = R2 * R, x3 = x * x * x;
    return PI * ((2.0/3.0) * R3 - R2 * x + (1.0/3.0) * x3);
}

vector<pair<ld, int>> holes;

ld ComputeSliceVolume(ld L, ld R) {
    ld res = 100 * 100 * (R - L);
    for (auto &[o, r] : holes) {
        if(o + r <= L || o - r >= R) continue;
        if(o + r <= R && o - r >= L) res -= SphereVolume(r);
        ld volume = SphereVolume(r);
        if (o - r < L) {
            ld sector_volume = GetSphericalSectorArea(L, o, r);
            res -= L > o ? sector_volume : volume - sector_volume;
            continue;
        }
        if (o + r > R) {
            ld sector_volume = GetSphericalSectorArea(R, o, r);
            res -= R < o ? sector_volume : volume - sector_volume;
            continue;
        }
    }
    return res;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);

    int n, s; cin >> n >> s; holes.resize(n);
    ld total_hole_volume = 0.0;
    for(int i = 0; i < n; ++i) {
        int r, x, y, z; cin >> r >> x >> y >> z;
        total_hole_volume += SphereVolume(r / 1000.0);
        holes[i] = {z / 1000.0 , r / 1000.0};
    }

    ld target_volume = (100 * 100 * 100 - total_hole_volume) / s;
    ld lastR = 0.0; vector<ld> res(1, 100);
    for(int i = 0; i < s - 1; i++) {
        ld L = lastR, R = 100.0;
        for(int j = 0; j < 40; ++j){
            ld M = (L + R) / 2.0;
            ComputeSliceVolume(lastR, M) < target_volume ? L = M : R = M;
        }
        ld cur = (L + R) / 2.0;
        res.push_back(res.back() - (cur - lastR));
        res[i] = cur - lastR; lastR = cur;
    }
    for(ld &t : res) cout << t << '\n';
}