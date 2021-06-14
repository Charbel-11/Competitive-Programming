#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
	int n;
	cin >> n;

	map<int, int> sor;
	vector<int> disks(n);
	for (int i = 0; i < n; i++) {
		cin >> disks[i];

		sor.insert({ disks[i], i });
	}

	int num = n - 1;
	while (num > 0) {
		int index = sor[num];
		if (index > 0 && disks[index - 1] >= disks[index] + 1) {
			disks[index - 1] = disks[index];
		}			
		else if (index < n - 1 && disks[index + 1] >= disks[index] + 1) {
			disks[index + 1] = disks[index];
		}
		else {
			cout << "NO" << endl; return 0;
		}

		num--;
	}

	cout << "YES" << endl;

}