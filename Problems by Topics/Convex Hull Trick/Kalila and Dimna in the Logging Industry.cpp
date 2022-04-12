// https://codeforces.com/contest/319/problem/C

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long ll;

const ll INF = LLONG_MAX;

struct Line {
    ll a, b; // y = ax + b
    Line(ll a = 0, ll b = INF) : a(a), b(b) {}
    Line(const Line& rhs) : a(rhs.a), b(rhs.b) {}

    ll eval(ll x) const {
        return a * x + b;
    }
};

struct Node {
    ll l, r; Line f;
    Node* left, * right;

    Node(ll l, ll r, const Line& _f) : l(l), r(r), f(_f), left(NULL), right(NULL) {}

    void pushDown() {
        if (l < r && !left) {
            ll m = l + (r - l) / 2;
            left = new Node(l, m, f);
            right = new Node(m + 1, r, f);
        }
    }

    void update(const Line& newLine) {
        pushDown();

        Line f1 = f, f2 = newLine;
        if (f1.eval(l) > f2.eval(l)) { swap(f1, f2); }
        if (f1.eval(r) <= f2.eval(r)) { f = f1; return; }

        if (l != r) {
            ll mid = l + (r - l) / 2;
            if (f1.eval(mid) > f2.eval(mid)) {
                f = f2; left->update(f1);
            }
            else {
                f = f1; right->update(f2);
            }
        }
    }

    ll getMin(ll x) const {
        ll ans = f.eval(x);

        ll mid = l + (r - l) / 2;
        if (x <= mid && left) { ans = min(ans, left->getMin(x)); }
        else if (mid < x && right) { ans = min(ans, right->getMin(x)); }

        return ans;
    }
};

// Given lines ax+b represented by (a,b) and one x s.t. minX<=x<=maxX, finds min/max(ax+b) over all lines (a,b) (without restrictions)
// Additions and queries run in O(log(maxX-minX))
// We can use doubles if needed; complexity becomes O(log(range/eps))
struct LiChaoTree {
    ll minX, maxX;
    Node* rootMin, * rootMax;

    LiChaoTree(ll _mi, ll _ma) : minX(_mi), maxX(_ma) {
        rootMin = new Node(minX, maxX, Line(0, INF));
        rootMax = new Node(minX, maxX, Line(0, INF));
    }

    void addLine(const Line& newLine) {
        rootMin->update(newLine);
    }

    ll getMin(ll x) const {
        return rootMin->getMin(x);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n; cin >> n;
    vector<ll> a(n); for (auto& x : a) { cin >> x; }
    vector<ll> b(n); for (auto& x : b) { cin >> x; }

    vector<ll> dp(n, INF); dp[0] = b[0];
    LiChaoTree LCT(0, 1e10);
    LCT.addLine(Line(b[0], dp[0]));
    for (int r = 1; r < n; r++) {
        dp[r] = b[r] + LCT.getMin(a[r] - 1);
        LCT.addLine(Line(b[r], dp[r]));
    }

    cout << dp[n - 1] << '\n';
}