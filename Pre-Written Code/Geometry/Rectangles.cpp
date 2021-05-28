#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
typedef long long ll;
const double pi = 3.14159265358979323846;

struct Rect {
	int x1, y1, x2, y2;		//(x1,y1) bot left point and (x2,y2) top right point
	Rect(int _x1, int _y1, int _x2, int _y2) :x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
	int area() { return (y2 - y1)*(x2 - x1); }
};
int intersectArea(Rect r1, Rect r2) {
	int xOverlap = max(0, min(r1.x2, r2.x2) - max(r1.x1, r2.x1));
	int yOverlap = max(0, min(r1.y2, r2.y2) - max(r1.y1, r2.y1));
	return xOverlap * yOverlap;
}
Rect intersectRect(Rect r1, Rect r2) {
	int x1 = max(r1.x1, r2.x1), x2 = min(r1.x2, r2.x2);
	int y1 = max(r1.y1, r2.y1), y2 = min(r1.y2, r2.y2);
	if (x1 > x2 || y1 > y2) { return Rect(0, 0, 0, 0); }
	else { return Rect(x1, y1, x2, y2); }
}