#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct Frac {
    ll num, denum; Frac() {}
    Frac(ll _num, ll _denum) {
        ll g = gcd(abs(_num), abs(_denum));
        num = _num / g; denum = _denum / g;
    }
    Frac(ll x) : Frac(x, 1) {}
    Frac(const Frac& rhs) : num(rhs.num), denum(rhs.denum) {}

    Frac operator *(const Frac& rhs) const { return Frac(num * rhs.num, denum * rhs.denum); }
    Frac operator +(const Frac& rhs) const { return Frac(num * rhs.denum + denum * rhs.num, denum * rhs.denum); }
    Frac operator -(const Frac& rhs) const { return Frac(num * rhs.denum - denum * rhs.num, denum * rhs.denum); }
    Frac operator /(const Frac& rhs) const { return Frac(num * rhs.denum, denum * rhs.num); }

    Frac operator *=(const Frac& rhs) { return *this = *this * rhs; }
    Frac operator +=(const Frac& rhs) { return *this = *this + rhs; }
    Frac operator -=(const Frac& rhs) { return *this = *this - rhs; }
    Frac operator /=(const Frac& rhs) { return *this = *this / rhs; }
    Frac absolute() const { return Frac(abs(num), abs(denum)); }
    bool operator ==(const Frac& rhs) const { return num == rhs.num && denum == rhs.denum; }
    bool operator <(const Frac& rhs) const {
        if (num != rhs.num)
            return num < rhs.num;
        return denum > rhs.denum;
    }
    template<class T> T eval() { return (T)num / (T)denum; }
};

struct Point {
    ll x, y; Point() {}
    Point(ll _x, ll _y) : x(_x), y(_y) {}
    Point(const Point& rhs) : x(rhs.x), y(rhs.y) {}

    bool operator == (const Point& rhs) const { return x == rhs.x && y == rhs.y; }
    Point operator - (const Point& rhs) const { return Point(x - rhs.x, y - rhs.y); }
    Point operator + (const Point& rhs) const { return Point(x + rhs.x, y + rhs.y); }

    friend istream& operator >> (istream& is, Point& p) { is >> p.x >> p.y; return is; }
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while(t--){
		int n; cin >> n;
        vector<Point> pts;
        for(int i = 0; i < n; i++){
            ll x,y; cin >> x >> y;
            pts.emplace_back(x, y);
        }

        vector<Point> ans;

        auto getSlopes = [&](int start){
            map<Frac, vector<int>> m;
            for(int i = 0; i < n; i++){
                if (i == start){ continue; }
                ll dy = pts[i].y - pts[start].y;
                ll dx = pts[i].x - pts[start].x;
                Frac curF(dy, dx);
                m[curF].push_back(i);
            }
            return m;
        };

        int A = 0;
        auto m = getSlopes(0);
        if (m.size() < 4 && m.size() > 1){
            stack<int> candidates;
            for(auto &it : m){
                for(int j = 0; j < min(4, (int)it.second.size()); j++){
                    candidates.push(it.second[j]);
                }
            }

            while(!candidates.empty()){
                int cur = candidates.top(); candidates.pop();
                m = getSlopes(cur);
                if (m.size() >= 4){
                    A = cur;
                    break;
                }
            }
        }

        if (m.size() >= 4){
            ans.push_back(pts[A]);
            for(auto &it : m){
                ans.push_back(pts[it.second[0]]);
                if (ans.size() == 5){ break; }
            }
        }

        if (ans.empty()){
            cout << "NO\n";
        }
        else{
            cout << "YES\n";
            for(auto &p : ans){
                cout << p.x << " " << p.y << '\n';
            }
        }
    }
}