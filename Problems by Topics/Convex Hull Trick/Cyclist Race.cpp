// https://www.codechef.com/JAN16/problems/CYCLRACE

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll INF = (ll)2e18;

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

    Node(int l, int r, const Line& _f) : l(l), r(r), f(_f), left(NULL), right(NULL) {}

    void pushDown() {
        if (l < r && !left) {
            int m = (l + r) >> 1;
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
            int mid = (l + r) >> 1;
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

        int mid = (l + r) >> 1;
        if (x <= mid && left) { ans = min(ans, left->getMin(x)); }
        else if (mid < x && right) { ans = min(ans, right->getMin(x)); }

        return ans;
    }
};

// Given lines ax+b and one x s.t. minX<=x<=maxX, finds min/max(ax+b) over all lines in O(log(maxX-minX))
// We can use doubles for minX, maxX if needed
struct LiChaoTree {
    ll minX, maxX;
    Node* rootMin, * rootMax;

    LiChaoTree(int _mi, int _ma) : minX(_mi), maxX(_ma) {
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


struct Cyclist {
    ll speed = 0, lastAccelerationTime = 0, lastPosition = 0;
};


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, q; cin >> n >> q;
    LiChaoTree LCT(0, 1e9 + 5);
    vector<Cyclist> cyclists(n);

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            ll time, i, newSpeed; cin >> time >> i >> newSpeed; i--;
            auto& curC = cyclists[i];

            ll newPos = curC.lastPosition + curC.speed * (time - curC.lastAccelerationTime);
            curC.lastPosition = newPos; curC.lastAccelerationTime = time; curC.speed = newSpeed;

            LCT.addLine(Line(newSpeed, newPos - newSpeed * time));
        }
        else {
            int time; cin >> time;
            ll ans = LCT.getMax(time);
            cout << (ans == -INF ? 0 : ans)  << '\n';
        }
    }
}