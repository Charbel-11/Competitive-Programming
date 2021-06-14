#include <iostream>
#include <string>

using namespace std;

int f(int n) {
	int res = n + 1;

	while (res % 10 == 0) {
		res = res / 10;
	}

	return res;
}

//Could have instead used a set to store reached numbers and stop when we get a number already present in the set

int main() {
	int num; 
	cin >> num;

	int newN = num;

	int totReach = 0;
//	bool gotTwo = false;	Useless since we could get to 5, then have 5 6 7 8 9 and 1 up to 9 again
//	Better to use a condition for number between 1 and 9 (base case)

	while (newN > 9) {
		totReach++;
		newN = f(newN);
	}
	totReach += 9;

	cout << totReach << endl;
}