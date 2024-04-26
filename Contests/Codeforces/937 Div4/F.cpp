#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int a, b, c; cin >> a >> b >> c;
        if (c == 0 || a != c-1){ cout << -1 << '\n'; continue; }

        int height = (b + c - 1) / c, bRem = b % c;
        int topLevel = bRem, bottomLevel = c - bRem;
        if (topLevel == 0){ topLevel = c; bottomLevel = 0; }

        for(int i = 0; i < a; i++){
            if (bottomLevel >= 2){
                bottomLevel -= 2; topLevel++;
            }
            else if (bottomLevel == 1){
                height++;
                bottomLevel = topLevel - 1;
                topLevel = 1;
            }
            else{
                height++;
                bottomLevel = topLevel - 2;
                topLevel = 1;
            }
        }

        cout << height << '\n';
	}
}

