#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

int v;

int min(int a, int b) {
	return a <= b ? a : b;
}

vector <int> divisors(int vv) {
	vector <int> ret1;
	vector <int> ret2;
	for (int i = 1; i <= int(sqrt(vv)) + 1; i++) {
		if (vv % i == 0) { ret1.push_back(i); ret2.insert(ret2.begin(), vv / i); }
	}

	int s1 = ret1.size();
	ret1.resize(ret1.size() + ret2.size());
	for (int i = 0; i < ret2.size(); i++) {
		ret1[s1 + i] = ret2[i];
	}
	return ret1;
}

int surf(int a, int b, int c) {
	return 2 * (a*b + a * c + b * c);
}

int minimum(vector <int> & divis) {
	int ret = surf(1, 1, v);
	for (int i = 0; i <= divis.size() / 2; i++) {
		int a = divis[i];
		int bb = v / a;
		vector <int> div2 = divisors(bb);
		for (int j = 0; j < div2.size() / 2; j++) {
			int b = div2[j];
			int c = bb / b;
			if (surf(a, b, c) < ret) { ret = surf(a, b, c); }
		}
	}
	return ret;
}

int main() {
	cin >> v;
	vector <int> div = divisors(v);
	/*for (auto &v : div) { cout << v << " "; }*/
	cout << minimum(div);
	cout << endl;

	return 0;
}