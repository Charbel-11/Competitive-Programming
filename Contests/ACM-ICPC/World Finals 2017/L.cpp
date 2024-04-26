#include <bits/stdc++.h>
using namespace std;

struct FT {
    int n; vector<int> vals;
    FT(int n) : n(n), vals(n + 1, 0ll) {}
    void update(int i, int x) {
        for (++i; i <= n; i += i & -i) vals[i] += x;
    }
    int query(int i) { // sum from 0 ... i
        int sum = 0;
        for (++i; i; i -= i & -i) sum += vals[i];
        return sum;
    }
    int query(int i, int j) { return query(j) - query(i - 1); }
};

struct Point{
    int match = -1;
    int realIdx, r, c; bool upLeft;
    Point(int _idx, int _r, int _c, bool _uL): realIdx(_idx), r(_r), c(_c), upLeft(_uL){}
    bool operator <(const Point& rhs) const{
        if (c != rhs.c){ return c < rhs.c; }
        return r < rhs.r;
    }
};

struct Segment{
    int c, r1, r2; bool start, duplicate=false;
    Segment (int _c, int _r1, int _r2, bool _s):c(_c), r1(_r1), r2(_r2), start(_s){}
    bool operator<(const Segment& rhs){
        if (c != rhs.c){ return c < rhs.c; }
        return start > rhs.start;
    }
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
    vector<int> comp;
    vector<pair<int, int>> oldPoints;
    for(int i = 0; i < 2 * n; i++){
        int r, c; cin >> r >> c;
        comp.push_back(r); comp.push_back(c);
        oldPoints.emplace_back(r, c);
    }
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());

    vector<Point> points;
    for(int i = 0; i < 2*n; i++){
        int r = lower_bound(comp.begin(), comp.end(), oldPoints[i].first) - comp.begin();
        int c = lower_bound(comp.begin(), comp.end(), oldPoints[i].second) - comp.begin();
        points.emplace_back(i, r, c, i<n);
    }
    sort(points.begin(), points.end());

    bool OK = true; map<int, int> activePoints;
    for(int i = 0; i < points.size(); i++){
        auto& p = points[i];
        if (p.upLeft){
            if (activePoints.count(p.r)){ OK = false; break; }
            activePoints.insert({p.r, i}); continue;
        }
        if (activePoints.empty()) { OK = false; break; }

        auto it = activePoints.upper_bound(p.r);
        if (it == activePoints.begin()){ OK = false; break; }
        it--;

        p.match = it->second;
        points[it->second].match = i;
        activePoints.erase(it);
    }
    if (!OK){ cout << "syntax error\n"; return 0; }

    vector<Segment> segments;
    for(auto &p : points){
        if (p.upLeft){
            auto &op = points[p.match];
            segments.emplace_back(p.c, p.r, op.r, true);
            segments.emplace_back(op.c, p.r, op.r, false);
            if (p.c == op.c){ segments.back().duplicate = true; }
        }
    }
    sort(segments.begin(), segments.end());

    FT ft(comp.size() + 1);
    for(auto &seg : segments){
        if (seg.start){
            if (ft.query(seg.r1, seg.r2) > 0) { OK = false; break; }
            ft.update(seg.r1, 1); ft.update(seg.r2, 1);
        }
        else{
            ft.update(seg.r1, -1); ft.update(seg.r2, -1);
        }
    }

    auto checkSegmentIntersection = [&](vector<pair<int, int>>& segments){
        if (segments.size() <= 1){ return; }
        sort(segments.begin(), segments.end());
        int L = segments[0].first, R = segments[0].second;
        for(int i = 1; i < segments.size(); i++){
            int curL = segments[i].first, curR = segments[i].second;
            if (curL > R){ L = curL; R = curR; }
            else { OK = false; break; }
        }
    };

    int curC = -1; vector<pair<int, int>> intervals;
    for(auto &seg : segments){
        if (seg.c != curC){
            curC = seg.c;
            checkSegmentIntersection(intervals);
            intervals.clear();
        }
        if (!seg.duplicate) intervals.push_back({seg.r1, seg.r2});
    }
    checkSegmentIntersection(intervals);
    if (!OK){ cout << "syntax error\n"; return 0; }

    vector<int> ans(n);
    for(auto &p : points){
        if (p.upLeft){
            ans[p.realIdx] = points[p.match].realIdx+1;
        }
    }
    for(auto &x : ans){ cout << x-n << '\n'; }
}

