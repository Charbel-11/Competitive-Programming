//https://codeforces.com/contest/13/problem/E

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

const int block = 320;
vector<int> power, nxt, cnt, last;
int N;

void compute(int i){
	int j = i + power[i];
	if (j >= N) {
		nxt[i] = -1; last[i] = i; cnt[i] = 1; 
		return; 
	}
	if ((i / block) != (j / block)) {
		nxt[i] = j; last[i] = i; cnt[i] = 1;
		return;
	}

	nxt[i] = nxt[j]; last[i] = last[j]; cnt[i] = cnt[j] + 1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int M; cin >> N >> M;
	power.resize(N); nxt.resize(N, -1); cnt.resize(N, 0); last.resize(N);
	for (auto &x : power) { cin >> x; }

	for (int i = N - 1; i >= 0; i--) { compute(i); }

	while (M--) {
		int op; cin >> op;
		if (op == 0) {
			int a, b; cin >> a >> b; a--;
			power[a] = b;

			for (int k = a; k >= 0 && (k / block) == (a / block); k--) {
				compute(k);
			}
		}
		else {
			int a; cin >> a; a--;
			int ans = 0, lastB = a;
			while (a != -1) { lastB = a; ans += cnt[a]; a = nxt[a]; }
			cout << last[lastB] + 1 << ' ' << ans << '\n';
		}
	}
}