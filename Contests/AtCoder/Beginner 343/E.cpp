#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int getIntersection3(int a1, int a2, int a3){
    vector<int> v = {a1, a2, a3};
    sort(v.begin(), v.end());
    a1 = v[0]; a2 = v[1]; a3 = v[2];
    int l = a3, r = a1 + 7;
    if (l > r){ return 0; }
    return r-l;
}

int getIntersection2(int a1, int a2){
    if (a1 > a2){ swap(a1, a2); }
    int l = a2, r = a1 + 7;
    if (l > r){ return 0; }
    return r-l;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

    int v1, v2, v3; cin >> v1 >> v2 >> v3;
	int a1 = 0, b1 = 0, c1 = 0; bool OK = false;
    if (v1 + 2 * v2 + 3 * v3 == 7 * 7 * 7 * 3) {
        for (int a2 = 0; a2 <= 8; a2++) {
            for (int b2 = -7; b2 <= 8; b2++) {
                for (int c2 = -7; c2 <= 8; c2++) {
                    for (int a3 = a2; a3 <= 15; a3++) {
                        for (int b3 = -14; b3 <= 15; b3++) {
                            for (int c3 = -14; c3 <= 15; c3++) {
                                int int3 = getIntersection3(a1, a2, a3) * getIntersection3(b1, b2, b3) *
                                           getIntersection3(c1, c2, c3);
                                if (int3 != v3) { continue; }

                                int int2_1 = getIntersection2(a1, a2) * getIntersection2(b1, b2) * getIntersection2(c1, c2) - int3;
                                int2_1 += getIntersection2(a1, a3) * getIntersection2(b1, b3) * getIntersection2(c1, c3) - int3;
                                int2_1 += getIntersection2(a2, a3) * getIntersection2(b2, b3) * getIntersection2(c2, c3) - int3;
                                if (int2_1 != v2){ continue; }

                                OK = true;
                                cout << "Yes\n";
                                cout << a1 << ' ' << b1 << ' ' << c1 << ' ';
                                cout << a2 << ' ' << b2 << ' ' << c2 << ' ';
                                cout << a3 << ' ' << b3 << ' ' << c3 << '\n';
                                goto endloop;
                            }
                        }
                    }
                }
            }
        }
    }
    endloop:
    if (!OK){ cout << "No\n"; }
}

