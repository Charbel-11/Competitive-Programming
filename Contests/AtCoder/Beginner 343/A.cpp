#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int a, b; cin >> a >> b;
    for(int i = 0; i <= 9; i++){
        if (i != a + b){ cout << i << '\n'; break; }
    }
}

