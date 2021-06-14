#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	int red, green; cin >> red >> green;
	int r, g, c; cin >> r >> g >> c;

	vector<ll> rA(r), gA(g), cA(c);
	for (auto &x : rA) { cin >> x; }
	for (auto &x : gA) { cin >> x; }
	for (auto &x : cA) { cin >> x; }

	sort(rA.rbegin(), rA.rend());
	sort(gA.rbegin(), gA.rend());
	sort(cA.rbegin(), cA.rend());

	vector<ll> candidates;
	ll ans = 0;
	for (int i = 0; i < red; i++) { candidates.push_back(rA[i]); }
	for (int i = 0; i < green; i++) { candidates.push_back(gA[i]); }
	for (int i = 0; i < min((int)cA.size(), red + green); i++) { candidates.push_back(cA[i]); }
	
	sort(candidates.rbegin(), candidates.rend());
	for (int i = 0; i < red + green; i++) { ans += candidates[i]; }

	cout << ans << endl;
}