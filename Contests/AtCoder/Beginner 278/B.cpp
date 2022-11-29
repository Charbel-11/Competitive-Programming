#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool isConfusing(int h, int m){
    int tR = m/10, bL = h%10;
    m -= tR * 10; m += bL * 10;
    h -= bL; h += tR;

    return h <= 23 && m <= 59 && h >= 0 && m >= 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int h, m; cin >> h >> m;
    while(!isConfusing(h, m)){
        m++;
        if (m == 60){
            m = 0; h++;
            if (h == 24){
                h = 0;
            }
        }
    }

    cout << h << " " << m << '\n';
}