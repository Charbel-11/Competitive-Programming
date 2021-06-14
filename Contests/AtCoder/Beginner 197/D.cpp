#include <iostream>
#include <string>
#include <map>
#include <set>
#include <complex>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

typedef complex<double> point;
#define x real()
#define y imag()
#define PI 3.1415926535897932384626

//Function for Rotation of P about Q by angle theta
point rotate(point P, point Q, double theta){
	return (P - Q) * polar(1.0, theta) + Q;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	double x0, y0, x2, y2; cin >> x0 >> y0 >> x2 >> y2;

	point Q((x0 + x2) / 2.0, (y0 + y2) / 2.0);
	point P(x2, y2);

	double angle = PI / (n / 2.0);
	angle *= -((n / 2.0) - 1);

	point ans = rotate(P, Q, angle);
	cout << fixed << setprecision(7) << ans.x << " " << ans.y << '\n';
}