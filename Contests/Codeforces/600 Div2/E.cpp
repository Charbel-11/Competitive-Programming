#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int n, m;
vector<int> street;

struct antenna {
	int center;
	int lRange, rRange, lMiss, rMiss;

	antenna(int c, int l1, int r1) { center = c; lRange = l1; rRange = r1; }
};

void updateAntennas(vector<antenna> &a) {
	for (int i = 0; i < n; i++) {
		int l = a[i].lRange - 1;
		while (l >= 1 && street[l] == 0) {
			l--;
		}
		a[i].lMiss = a[i].lRange - l - 1;

		int r = a[i].rRange + 1;
		while (r <= m && street[r] == 0) {
			r++;
		}
		a[i].rMiss = r - a[i].rRange - 1;
	}
}

long long coeff(antenna &a) {
	long long c1 = (long long)a.lMiss;
	long long c2 = (long long)a.rMiss;
	return c1 * c2;
}

bool comp(antenna &a1, antenna &a2) {
	return a1.center < a2.center;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> m;
	street.resize(m + 2, 0);
	vector<antenna> a;

	for (int i = 0; i < n; i++) {
		int x, s; cin >> x >> s;

		a.push_back(antenna(x, x - s, x + s));
		int l = x - s, r = x + s;
		if (l < 1) { l = 1; }
		if (r > m) { r = m; }
		street[l]++; street[r + 1]--;
	}

	sort(a.begin(), a.end(), comp);

	int remaining = (street[1] == 0);
	for (int i = 2; i < m + 1; i++) {
		street[i] += street[i - 1];
		if (street[i] == 0) { remaining++; }
	}
	updateAntennas(a);

	int res = 0;
	while (remaining) {
		int bestChoice = 0;
		long long curBest = coeff(a[0]);

		for (int i = 1; i < n; i++) {
			long long cur = coeff(a[i]);
			if (cur > curBest) {
				bestChoice = i;
				curBest = cur;
			}
		}

		res++;
		if (a[bestChoice].lMiss > 0 && a[bestChoice].rMiss > 0) { remaining -= 2; }
		else { remaining -= 1; }
		a[bestChoice].lRange--; a[bestChoice].rRange++;
		if (a[bestChoice].lRange <= 0) { a[bestChoice].lRange = 1; }
		if (a[bestChoice].rRange >= m) { a[bestChoice].rRange = m; }
		street[a[bestChoice].lRange]++; street[a[bestChoice].rRange]++;

		for (int i = 0; i < n; i++) {
			if (i == bestChoice) { continue; }
			if (a[i].rRange + a[i].rMiss == a[bestChoice].lRange) {
				a[i].rMiss--;
				if (a[i].rMiss < 0) { a[i].rMiss = 0; }
			}
			else if (a[i].lRange - a[i].lMiss == a[bestChoice].lRange) {
				a[i].lMiss--;
				if (a[i].lMiss < 0) { a[i].lMiss = 0; }
			}
			else if (a[i].lRange - a[i].lMiss == a[bestChoice].rRange) {
				a[i].lMiss--;
				if (a[i].lMiss < 0) { a[i].lMiss = 0; }
			}
			else if (a[i].rRange + a[i].rMiss == a[bestChoice].rRange) {
				a[i].rMiss--;
				if (a[i].rMiss < 0) { a[i].rMiss = 0; }
			}
		}
	}

	cout << res << endl;
}