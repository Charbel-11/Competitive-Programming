#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;
typedef long long ll;

double pev(ll k, double pflip, vector<double>& prob) {
	if (k == 0) { return 1; }
	if (prob[k] > -0.9) { return prob[k]; }
	return  prob[k] = pflip * (1 - pev(k - 1, pflip, prob)) + (1 - pflip)*pev(k - 1, pflip, prob);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream ifs("fetiera.in");
	int t; ifs >> t;
	
	while (t--) {
		int n, k; ifs >> n >> k;
		ll choice = (n + 1)*n / 2;
		ll total = choice * choice;

		double expected = 0;
				
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int cur; ifs >> cur;

				ll in = (ll)(i + 1)*(n - i)*(j + 1)*(n - j);
				double p = (double)in / total;

				vector<double> prob(302, -1);

				if (cur) { expected += pev(k, p, prob); }	
				else { expected += (1 - pev(k, p, prob)); }
			}
		}

		cout << setprecision(6) << expected << endl;
	}
}