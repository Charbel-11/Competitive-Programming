#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
typedef long long ll;
const double pi = 3.14159265358979323846;

//PICK's theorem
//I=A-(B/2)+1=(area()-bdry())/2+1, where A is the area of a lattice polygon, I is number of lattice points inside it, and B is number of 
//lattice points on the boundary (A lattice point is a point at the intersection of two or more grid lines)
vector<pair<ll, ll>> p;		//points in clockwise order
int n;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

//Polygon area * 2, need the points in clockwise order
ll area() {
	ll a = 0;
	for (int i = 0; i < n; i++) {
		a += (p[i].first * p[(i + 1)%n].second - p[(i + 1)%n].first * p[i].second);
	}
	return abs(a);
}

ll bdry() {
	ll B = 0;
	for (int i = 0; i < n; i++) {
		ll x = abs(p[i].first - p[i + 1].first);
		ll y = abs(p[i].second - p[i + 1].second);
		B += gcd(x, y);
	}
	return B;
}