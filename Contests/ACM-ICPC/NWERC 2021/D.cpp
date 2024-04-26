#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
    ll x, y; Point() {}
    Point(ll _x, ll _y) : x(_x), y(_y) {}
    Point(const Point& rhs) : x(rhs.x), y(rhs.y) {}

    bool operator == (const Point& rhs) const { return x == rhs.x && y == rhs.y; }
    Point operator - (const Point& rhs) const { return Point(x - rhs.x, y - rhs.y); }
    Point operator + (const Point& rhs) const { return Point(x + rhs.x, y + rhs.y); }
    bool operator < (const Point& rhs) const {
        if (x != rhs.x) return x < rhs.x;
        return y < rhs.y;
    }

    friend istream& operator >> (istream& is, Point& p) { is >> p.x >> p.y; return is; }
};

ll crossProduct(const Point& A, const Point& B) { return A.x * B.y - A.y * B.x; }

//0: Colinear; 1: Clockwise (C is to the right of (AB)); 2: Counterclockwise (C is to the left of (AB))
int orientation(const Point& A, const Point& B, const Point& C) {
    ll x = crossProduct(C - B, B - A);
    return x ? 1 + (x < 0) : 0;
}

// Returns the Convex Hull Sorted Clockwise in O(nlogn)
vector<Point> convexHullGrahamScan(vector<Point> P) {
    sort(P.begin(), P.end());
    P.erase(unique(P.begin(), P.end()), P.end());

    int n = (int)P.size();
    if (n < 3) { return P; }

    vector<Point> res;
    auto incorrect = [&](const Point& A, const Point& B, const Point& C) {
        //Change to != 1 to remove points on CH boundary
        return orientation(A, B, C) == 2;
    };

    for (int i = 0; i < n; i++) {
        while (res.size() > 1 && incorrect(res.end()[-2], res.end()[-1], P[i])) { res.pop_back(); }
        res.push_back(P[i]);
    }

    int m = (int)res.size();
    for (int i = n - 2; i >= 0; i--) {
        if (P[i] == res.end()[-2]) { continue; }
        while (res.size() > m && incorrect(res.end()[-2], res.end()[-1], P[i])) { res.pop_back(); }
        res.push_back(P[i]);
    }

    res.pop_back();
    return res;
}

int solve(vector<Point> P){
    auto CH = convexHullGrahamScan(P);
    int ans = CH.size() * 3;
    for(int i = 0; i < CH.size(); i++){
        int j = (i + 1) % CH.size();
        ans += max(abs(CH[i].x - CH[j].x), abs(CH[i].y - CH[j].y)) - 2;
    }
    return ans;
}

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n; cin >> n; vector<Point> P;
    for(int i = 0; i < n; i++){
        int x, y; cin >> x >> y;
        P.emplace_back(x, y);
    }

    int ans = INT_MAX;
    for(int i = 0; i < 4; i++){
        P.emplace_back(P[0].x + dx[i], P[0].y + dy[i]);
        ans = min(ans, solve(P));
        P.pop_back();
    }

    if (n == 2){
        if (P[0].x == P[1].x && abs(P[0].y - P[1].y) == 1){ cout << 6 << '\n'; }
        else if (P[0].y == P[1].y && abs(P[0].x - P[1].x) == 1){ cout << 6 << '\n'; }
        else { cout << ans + 1 << '\n'; }
    }
    else{ cout << ans << '\n'; }
}