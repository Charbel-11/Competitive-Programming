#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int A, B; cin >> A >> B;
    if (A % 3 != 0 && A+1 == B){ cout << "Yes\n"; }
    else { cout << "No\n"; }
}

