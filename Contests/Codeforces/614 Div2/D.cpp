#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ll x0, y0; cin >> x0 >> y0;
	ll ax, ay, bx, by; cin >> ax >> ay >> bx >> by;

	ll xs, ys; cin >> xs >> ys;
	ll t; cin >> t;
	
	vector<pair<ll, ll>> nodes;
	ll prevDist = abs(x0 - xs) + abs(y0 - ys);
	ll dist = abs(x0 - xs) + abs(y0 - ys);
	while (dist > t) {
		x0 = x0 * ax + bx;
		y0 = y0 * ay + by;
		dist = abs(x0 - xs) + abs(y0 - ys);
		if (dist > prevDist) { break; }
		prevDist = dist;
	}
	while (abs(x0 - xs) + abs(y0 - ys) <= t) {
		nodes.push_back({ x0, y0 });
		x0 = x0 * ax + bx;
		y0 = y0 * ay + by;
	}

	ll maxCollected = 0;
	for (int pos = 0; pos <= nodes.size(); pos++) {
		ll collected = 0;
		ll timeRemaining = t;
		ll curX = xs, curY = ys;

		//Starting left
		for (int i = pos - 1; i >= 0; i--) {
			ll xT = nodes[i].first, yT = nodes[i].second;
			ll neededTime = abs(curX - xT) + abs(curY - yT);
			if (neededTime <= timeRemaining) {
				timeRemaining -= neededTime;
				collected++;
				curX = xT; curY = yT;
			}
		}
		curX = xs; curY = ys;
		for (int i = pos; i < nodes.size(); i++) {
			ll xT = nodes[i].first, yT = nodes[i].second;
			ll neededTime = abs(curX - xT) + abs(curY - yT); neededTime *= 2;
			if (neededTime <= timeRemaining) {
				timeRemaining -= neededTime;
				collected++;
				curX = xT; curY = yT;
			}
		}
		maxCollected = max(maxCollected, collected);

		//Starting right
		collected = 0;
		timeRemaining = t;
		curX = xs; curY = ys;

		for (int i = pos; i < nodes.size(); i++) {
			ll xT = nodes[i].first, yT = nodes[i].second;
			ll neededTime = abs(curX - xT) + abs(curY - yT);
			if (neededTime <= timeRemaining) {
				timeRemaining -= neededTime;
				collected++;
				curX = xT; curY = yT;
			}
		}
		curX = xs; curY = ys;
		for (int i = pos - 1; i >= 0; i--) {
			ll xT = nodes[i].first, yT = nodes[i].second;
			ll neededTime = abs(curX - xT) + abs(curY - yT); neededTime *= 2;
			if (neededTime <= timeRemaining) {
				timeRemaining -= neededTime;
				collected++;
				curX = xT; curY = yT;
			}
		}
		maxCollected = max(maxCollected, collected);
	}

	cout << maxCollected << endl;
}