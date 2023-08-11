#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const double pi = 3.14159265358979323846;

struct Point {
	double x, y, z; Point() {}
	Point(double _x, double _y, double _z) :
		x(_x), y(_y), z(_z) {}
};

//Finds the tangent length from an external point p to a sphere of radius R (centered at 0)
double tanLength(Point &p) { return p.x * p.x + p.y * p.y + p.z * p.z - R * R; }

Point sphericalToCartesian(const double &r, const double &lo, const double &la) {
	return Point(r * sin(la) * cos(lo), r * sin(la) * sin(lo), r * cos(la));
}

double dist2(Point &p1, Point &p2) {
	double dx = p1.x - p2.x, dy = p1.y - p2.y, dz = p1.z - p2.z;
	return dx * dx + dy * dy + dz * dz;
}

void rotatePoint(double &x, double &y, double angle) {
	double X = x * cos(angle) - y * sin(angle);
	double Y = x * sin(angle) + y * cos(angle);
	x = X; y = Y;
}

double toRadians(double p) { return (p * pi) / 180.0; }