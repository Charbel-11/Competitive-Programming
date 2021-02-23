#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <bitset>
using namespace std;
typedef long long ll;

struct Frac {
	ll num, denum; Frac() {}
	ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
	Frac(ll _n, ll _d) {
		ll g = gcd(abs(_n), abs(_d));
		num = abs(_n) / g; denum = abs(_d) / g;
		if ((_n < 0) ^ (_d < 0)) { num = -num; }
	}
	Frac(ll x) : num(x), denum(1) {}
	Frac operator *(const Frac &rhs) { return Frac(num * rhs.num, denum * rhs.denum); }
	Frac operator +(const Frac &rhs) { return Frac(num * rhs.denum + denum * rhs.num, denum * rhs.denum); }
	Frac operator -(const Frac &rhs) { return Frac(num * rhs.denum - denum * rhs.num, denum * rhs.denum); }
	Frac operator /(const Frac &rhs) { return Frac(num * rhs.denum, denum * rhs.num); }
	Frac operator +=(const Frac &rhs) { return (*this) = (*this) + rhs; }
	Frac operator -=(const Frac &rhs) { return (*this) = (*this) - rhs; }
	Frac operator *=(const Frac &rhs) { return (*this) = (*this) * rhs; }
	Frac operator /=(const Frac &rhs) { return (*this) = (*this) / rhs; }
	bool operator ==(const Frac &rhs) const { return num == rhs.num && denum == rhs.denum; }
	bool operator <(const Frac &rhs) const { return num * rhs.denum < denum * rhs.num; }
	bool operator >(const Frac &rhs) const { return num * rhs.denum > denum * rhs.num; }
};

ostream& operator <<(ostream &os, const Frac &rhs) {
	long double n = rhs.num, d = rhs.denum;
	os << n / d; return os;
} 

void normalize(Frac &f) {
	if (!f.num) { return; }
	ll x = f.denum / f.num;
	if (x > (ll)1e12) { f = Frac(0); }
}