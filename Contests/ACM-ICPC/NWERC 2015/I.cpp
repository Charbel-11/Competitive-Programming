#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string s; cin >> s;
    int i = 0, j = 0;
    int curRange = (1 << (s.size() - 1));
    for(auto c : s){
        if (c == '1'){ j += curRange; }
        else if (c == '2'){ i += curRange; }
        else if (c == '3'){ i += curRange; j += curRange; }
        curRange /= 2;
    }

    cout << s.size() << ' ' << j << ' ' << i << '\n';
}

