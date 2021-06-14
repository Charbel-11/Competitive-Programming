#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <stack>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

struct competitor {
	competitor *left, *right, *top, *bot;
	int interest;

	competitor() {}
	competitor(int it) :interest(it) { left = right = top = bot = NULL; }

	bool willLoose() {
		int oppScore = 0, oppNum = 0;
		if (left) { oppNum++; oppScore += left->interest; }
		if (right) { oppNum++; oppScore += right->interest; }
		if (top) { oppNum++; oppScore += top->interest; }
		if (bot) { oppNum++; oppScore += bot->interest; }
		if (oppNum * interest < oppScore) { return true; }
		return false;
	}

	void update() {
		while (top && top->interest == 0) { top = top->top; }
		while (bot && bot->interest == 0) { bot = bot->bot; }
		while (left && left->interest == 0) { left = left->left; }
		while (right && right->interest == 0) { right = right->right; }
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	for (int q = 1; q <= t; q++) {
		int R, C; cin >> R >> C;

		vector<vector<competitor>> comps(R, vector<competitor>(C));
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				int nn; cin >> nn;
				comps[i][j] = competitor(nn);
			}
		}
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (j < C-1){
					comps[i][j].right = &comps[i][j + 1];
					comps[i][j + 1].left = &comps[i][j];
				}
				if (i < R - 1) {
					comps[i][j].bot = &comps[i + 1][j];
					comps[i + 1][j].top = &comps[i][j];
				}
			}
		}		

		ll ans = 0, curInterest = 0;
		vector<competitor*> loosers, toCheck;
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				ans += comps[i][j].interest;
				if (comps[i][j].willLoose()) { loosers.push_back(&comps[i][j]);	}
			}
		}
		curInterest = ans;

		while (!loosers.empty()) {
			for (auto &c : loosers) {
				curInterest -= c->interest; c->interest = 0;
				if (c->top) { toCheck.push_back(c->top); }
				if (c->bot) { toCheck.push_back(c->bot); }
				if (c->left) { toCheck.push_back(c->left); }
				if (c->right) { toCheck.push_back(c->right); }
			}
			loosers.clear(); ans += curInterest;
			while (!toCheck.empty()) {
				auto cmp = toCheck.back(); toCheck.pop_back();
				if (!cmp->interest) { continue; }

				cmp->update();
				if (cmp->willLoose()) { loosers.push_back(cmp); }
			}
		}

		cout << "Case #" << q << ": " << ans << endl;
	}
}