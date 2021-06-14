#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int main() {
	double n;
	cin >> n;
	vector<double> q;
	for (int i = 0; i < n - 1; i++) {
		double t;
		cin >> t;
		q.push_back(t);
	}

	double p1 = (n + 1) / 2.0;
	for (int i = 0; i < n - 1; i++) {
		p1 -= double((n - i - 1)*q[i] / n);
	}

	bool work = true;
	vector<int> answ(n,0);
	set<int> visited;
	answ[0] = ceil(p1);					//used ceil and floor to avoid working with doubles
	visited.insert(answ[0]);			//Can't have repetition
	if (answ[0]<1 || answ[0]>n) {		//We need to check the first element since we aren't doing it after
		work = false;
	}

	for (int i = 1; i < n; i++) {
		answ[i] = answ[i - 1] + q[i - 1];
		
		if (visited.count(answ[i]) == 0) {
			visited.insert(answ[i]);
		}
		else {
			work = false;
			break;
		}

		if (answ[i] < 1 || answ[i] > n) {
			work = false;
			break;
		}
	}

	if (!work) {					//If floor = ceil, and work == false, we should print -1
		visited.clear();
		answ[0] = floor(p1);
		visited.insert(answ[0]);
		if (answ[0]<1 || answ[0]>n) {
			cout << -1 << endl;
			return 0;
		}

		for (int i = 1; i < n; i++) {
			answ[i] = answ[i - 1] + q[i - 1];
			if (visited.count(answ[i]) == 0) {
				visited.insert(answ[i]);
			}
			else {
				cout << -1 << endl;
				return 0;
			}
			if (answ[i] < 1 || answ[i] > n) {
				cout << -1 << endl;
				return 0;
			}
		}
	}
	
	for (int i = 0; i < n; i++) {
		cout << answ[i] << " ";
	}
	cout << endl;
}