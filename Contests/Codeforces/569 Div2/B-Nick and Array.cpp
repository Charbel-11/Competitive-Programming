#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
	int n;
	cin >> n;

	vector<int> numbers(n);
	for (int i = 0; i < n; i++) {
		cin >> numbers[i];
	
		if (numbers[i] >= 0) {
			numbers[i] = -numbers[i] - 1;
		}
	}

	if (n % 2 == 1) {
		int maxInd = 0;
		int maxAbs = -numbers[0];

		for (int i = 1; i < n; i++) {
			if (-numbers[i] > maxAbs) {
				maxAbs = -numbers[i];
				maxInd = i;
			}
		}

		numbers[maxInd] = -numbers[maxInd] - 1;
	}

	for (int i = 0; i < n; i++) {
		cout << numbers[i] << " ";
	}
	cout << endl;
}