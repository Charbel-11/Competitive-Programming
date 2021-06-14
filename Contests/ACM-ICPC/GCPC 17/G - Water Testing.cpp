#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

typedef long long ll;
vector<pair<ll, ll>> p;
int n;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

long long area() {
	long long a = 0;
	for (int i = 0; i < n; i++) {
		a += (p[i].first*p[i + 1].second - p[i + 1].first*p[i].second);
	}
	return abs(a);
}

long long bdry() {
	ll B = 0;
	for (int i = 0; i < n; i++) {
		ll x = abs(p[i].first - p[i + 1].first);
		ll y = abs(p[i].second - p[i + 1].second);
		B += gcd(x, y);
	}
	return B;
}

int main() {
	cin >> n; p.resize(n);
	for (int i = 0; i < n; i++) {
		ll x, y; cin >> x >> y; p[i] = { x,y };
	}
	p.push_back({ p[0].first, p[0].second });
	ll I = (area() - bdry()) / 2 + 1;
	cout << I << endl;
}