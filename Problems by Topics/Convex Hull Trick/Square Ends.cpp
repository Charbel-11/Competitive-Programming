// https://csacademy.com/contest/archive/task/squared-ends/statement/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll INF = (ll)4e17;

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
            ll m = (l + r) >> 1;
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
            ll mid = (l + r) >> 1;
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

        ll mid = (l + r) >> 1;
        if (x <= mid && left) { ans = min(ans, left->getMin(x)); }
        else if (mid < x && right) { ans = min(ans, right->getMin(x)); }

        return ans;
    }
};

// Given lines ax+b and one x s.t. minX<=x<=maxX, finds min/max(ax+b) over all lines (a,b) (without restrictions)
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

        Line newLineMax(newLine);
        newLineMax.a *= -1; newLineMax.b *= -1;
        rootMax->update(newLineMax);
    }

    ll getMin(ll x) const {
        return rootMin->getMin(x);
    }
    ll getMax(ll x) const {
        return -rootMax->getMin(x);
    }
};

ll dp[10002][103];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, K; cin >> N >> K;
    vector<ll> A(N); for (auto& x : A) { cin >> x; }
    vector<LiChaoTree> LCTs;
    for (int i = 0; i <= K; i++) { LCTs.push_back(LiChaoTree(0, 1e8)); }

    for (int i = 0; i <= N; i++)
        for (int k = 0; k <= K; k++)
            dp[i][k] = INF;
    dp[0][0] = 0;

    for (int i = 1; i <= N; i++) {
        for (int k = 1; k <= min(i, K); k++) {
            if (dp[i - 1][k - 1] < INF)
                LCTs[k - 1].addLine(Line(-2 * A[i - 1], A[i - 1] * A[i - 1] + dp[i - 1][k - 1]));
            dp[i][k] = A[i - 1] * A[i - 1] + LCTs[k - 1].getMin(A[i - 1]);
        }
    }

    cout << dp[N][K] << '\n';
}