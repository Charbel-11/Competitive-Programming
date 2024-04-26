#include <bits/stdc++.h>
using namespace std;

bool isKQuotation(const vector<int>& a, int k, int i, int j, int valStart, int valEnd){
    if (k > valStart || k > valEnd || i > j){ return false; }
    if (i == j){
        if (valStart < 2 * k){ return false; }
        if (k == 1){ return (valStart % 2) == 0; }
        return isKQuotation(a, k-1, i, i, valStart - 2 * k, valStart - 2 * k);
    }
    if (k == 1){
        int curSum = valStart + valEnd;
        for(int l = i + 1; l < j; l++){ curSum += a[l]; }
        return (curSum % 2) == 0;
    }

    int newI = i, newJ = j, newValStart = valStart - k, newValEnd = valEnd - k;
    if (newValStart == 0){
        newValStart = a[i+1]; newI++;
        if (newI == newJ){ newValStart = newValEnd; }
    }
    if (newValEnd == 0){
        newValEnd = a[j-1]; newJ--;
        if (newJ == newI){ newValEnd = newValStart; }
    }
    return isKQuotation(a, k-1, newI, newJ, newValStart, newValEnd);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    vector<int> a(n); for(auto &x : a){ cin >> x; }

    int ans = 0;
    if ((n == 2 && a[0] == 1 && a[1] == 1) || (n==1 && a[0] == 2)){ ans = 1; }
    for(int k = min(a[0], a[n-1]); k >= 2; k--){
        if (isKQuotation(a, k, 0, n-1, a[0], a[n-1])){ ans = k; break; }
    }

    if (ans > 0){ cout << ans << '\n'; }
    else { cout << "no quotation\n"; }
}

