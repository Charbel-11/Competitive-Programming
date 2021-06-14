#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> numbers(n);
	for (int i = 0; i < n; i++) {
		cin >> numbers[i];
	}
	sort(numbers.rbegin(), numbers.rend());

	int odd = 0;
	int even = 0;

	for (int i = 0; i < n; i++) {
		if (numbers[i] % 2 == 0) {
			even++;
		}
		else {
			odd++;
		}
	}

	if (odd > even) {
		odd = even + 1;			//num to remove
	}
	else {
		even = odd + 1;			//num to remove
	}

	int remainder = 0;
	for (int i = 0; i < n; i++) {
		if (even>0 && numbers[i] % 2 == 0) {
			even--;
		}
		else if (odd > 0 && numbers[i] % 2 == 1) {
			odd--;
		}
		else {
			remainder += numbers[i];
		}
	}

	cout << remainder << endl;
}