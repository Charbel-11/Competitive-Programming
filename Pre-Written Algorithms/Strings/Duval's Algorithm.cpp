#include <bits/stdc++.h>
using namespace std;

// Finds in O(n) a factorization s=w_1…w_k where w_1≥⋯≥w_k and
// w_i is simple ∀i: it is strictly smaller than all its non-trivial suffixes
vector<string> duval(string s) {
    int n = (int)s.size(); vector<string> fact;
    int i = 0; while (i < n) {
        int j = i + 1, k = i;
        while (j<n && s[k]<=s[j]) { s[k]<s[j] ? k = i : k++; j++; }
        while(i<=k){fact.push_back(s.substr(i, j-k)); i += j - k; }
    }
    return fact;
}

// Runs in O(n)
string minCyclicShift(string s) {
    s += s; int n = (int) s.size(), start = 0;
    int i = 0; while (i < n / 2) {
        start = i; int j = i + 1, k = i;
        while (j<n && s[k]<=s[j]) { s[k]<s[j] ? k = i : k++; j++; }
        while (i <= k) i += j - k;
    }
    return s.substr(start, n >> 1);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

}

