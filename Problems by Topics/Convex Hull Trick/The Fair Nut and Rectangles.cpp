//https://codeforces.com/contest/1083/problem/E

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
using namespace std;
typedef long long ll;


const ll INF = (ll)5e18;

struct Line {
    ll a, b; // y = ax + b
    Line(ll a = 0, ll b = INF) : a(a), b(b) {}
    Line(const Line& rhs) : a(rhs.a), b(rhs.b) {}

    ll eval(ll x) {
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

    ll getMin(ll x) {
        ll ans = f.eval(x);

        ll mid = (l + r) >> 1;
        if (x <= mid && left) { ans = min(ans, left->getMin(x)); }
        else if (mid < x && right) { ans = min(ans, right->getMin(x)); }

        return ans;
    }
};

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

    ll getMin(ll x) {
        return rootMin->getMin(x);
    }
    ll getMax(ll x) {
        return -rootMax->getMin(x);
    }
};

struct rect {
    ll x, y, a;

    bool operator <(const rect& rhs) {
        return x < rhs.x;
    }

    friend istream& operator >> (istream& is, rect& r) { is >> r.x >> r.y >> r.a; return is; }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n; cin >> n;
    vector<rect> rectangles(n);
    for (auto& r : rectangles) { cin >> r; }
    sort(rectangles.begin(), rectangles.end());

    vector<ll> dp(n, 0);
    LiChaoTree CHT(1, 1e9 + 10);
    for (int i = 0; i < n; i++) {
        if (i) { dp[i] = CHT.getMax(rectangles[i].y); }
        if (dp[i] < 0) { dp[i] = 0; }
        dp[i] += rectangles[i].x * rectangles[i].y - rectangles[i].a;
        CHT.addLine(Line(-rectangles[i].x, dp[i]));
    }

    ll ans = *max_element(dp.begin(), dp.end());
    cout << ans << '\n';
}