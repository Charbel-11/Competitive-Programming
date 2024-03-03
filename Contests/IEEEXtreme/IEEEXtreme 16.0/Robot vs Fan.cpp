#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mod;

ll exGcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll x1, y1; ll d = exGcd(b, a % b, x1, y1);
    x = y1; y = x1 - y1 * (a / b);
    return d;
}

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return (a / gcd(a, b)) * b; }

bool find_any_solution(ll a, ll b, ll c, ll& x0, ll& y0, ll& g) {
    g = exGcd(abs(a), abs(b), x0, y0);
    if (c % g)  return false;

    x0 *= c / g; y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

void shift_solution(ll& x, ll& y, ll a, ll b, ll cnt) {
    x += cnt * b; y -= cnt * a;
}

ll find_all_solutions(ll a, ll b, ll c, ll minx, ll maxx, ll miny, ll maxy) {
    ll x, y, g;
    if (!find_any_solution(a, b, c, x, y, g)) return -1e10;
    a /= g; b /= g;

    int sign_a = a > 0 ? +1 : -1;
    int sign_b = b > 0 ? +1 : -1;

    shift_solution(x, y, a, b, (minx - x) / b);
    if (x < minx) shift_solution(x, y, a, b, sign_b);
    if (x > maxx) return -1e10;
    ll lx1 = x;

    shift_solution(x, y, a, b, (maxx - x) / b);
    if (x > maxx) shift_solution(x, y, a, b, -sign_b);
    ll rx1 = x;

    shift_solution(x, y, a, b, -(miny - y) / a);
    if (y < miny) shift_solution(x, y, a, b, -sign_a);
    if (y > maxy) return -1e10;
    ll lx2 = x;

    shift_solution(x, y, a, b, -(maxy - y) / a);
    if (y > maxy) shift_solution(x, y, a, b, sign_a);
    ll rx2 = x;

    if (lx2 > rx2) swap(lx2, rx2);
    ll lx = max(lx1, lx2);
    ll rx = min(rx1, rx2);

    return lx > rx ? -1e10 : lx;
}

map<char, int> dx = { {'v', 1}, {'^', -1} };
map<char, int> dy = { {'<', -1}, {'>', 1} };

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t; cin >> t;
    while (t--) {
        int r; cin >> r; vector<string> v(r);
        for (auto& x : v) cin >> x;
        vector<pair<int, int>> dust;

        int d; cin >> d;
        for (int i = 0; i < d; i++) {
            int x, y; cin >> x >> y;
            dust.emplace_back(x, y);
        }

        ll tail = -1; bool ok = false;
        vector<pair<int, int>> robot(1, { 0, 0 });
        vector<vector<int>> vis(r, vector<int>(r, -1));
        vis[0][0] = 0;

        for (int i = 1, j = 0; true; i++, j = (j + 1) % d) {
            //We found a trivial match by passing by the tail of the robot cycle
            if (robot.back() == dust[j]) { tail = i - 1; ok = true; break; }

            //Getting the coordinates of the current and next positions
            int x, y; tie(x, y) = robot.back();
            int nx = x + dx[v[x][y]], ny = y + dy[v[x][y]];

            //New cell, append it to path and continue
            if (vis[nx][ny] == -1) { vis[nx][ny] = i; robot.emplace_back(nx, ny); continue; }

            //Rotate dust period so that it corresponds with first cycle node
            rotate(dust.begin(), dust.begin() + (j + 1) % d, dust.end());

            //Remove tail nodes from robot path since they don't belong to the cycle
            robot.erase(robot.begin(), robot.begin() + vis[nx][ny]);

            //Mark Tail length so that we add it in the end
            tail = i; break;
        }

        //Match was found trivially
        if (ok) { cout << tail << '\n'; continue; }


        //Save positions of appearance of each cell in dust period
        vector<vector<vector<int>>> dustIDX(r, vector<vector<int>>(r));
        for (int i = 0; i < d; i++)
            dustIDX[dust[i].first][dust[i].second].push_back(i);

        int A = (int)robot.size();
        ll res = 1ll << 60, mod = lcm(A, d);
        for (int i = 0; i < A; i++) {
            int x, y; tie(x, y) = robot[i];
            for (auto& j : dustIDX[x][y]) {

                //For every (robot cell X / occurence of that cell in dust period Y)
                //Find solutions of X + Au = Y + Dv i.e Au - Dv = Y - X
                ll S = find_all_solutions(A, -d, j - i, 0, d, 0, A);

                //When we find a solution we take it modulo LCM to get the first one
                if (S != -1e10){
                    ll cur = (i + A * S) % mod;
                    if (cur < 0){ cur += mod; }
                    res = min(res, cur);
                }
            }
        }

        if (res == 1ll << 60) { cout << "never\n"; continue; }
        cout << res + tail << '\n';
    }
}