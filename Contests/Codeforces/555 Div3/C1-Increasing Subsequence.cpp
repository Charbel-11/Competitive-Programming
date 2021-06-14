#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector <int> numbers(n);
	for (int i = 0; i < n; i++) {
		cin >> numbers[i];
	}

	string r = "";
	int lastEl = -1;			//We just need to remember the last element, not the whole vector
	int a = 0;
	int b = n - 1;

	//Think about all cases where we can take numbers[a]
	while (a <= b) {
		if (numbers[a] < numbers[b]) {
			if (numbers[a] > lastEl) {
				lastEl = numbers[a];
				r += 'L';
				a++;
			}
			else if (numbers[b] > lastEl) {
				lastEl = numbers[b];
				r += 'R';
				b--;
			}
			else { break; }
		}
		else {
			if (numbers[b] > lastEl) {
				lastEl = numbers[b];
				r += 'R';
				b--;
			}
			else if (numbers[a] > lastEl) {
				lastEl = numbers[a];
				r += 'L';
				a++;
			}
			else { break; }
		}
	}

	cout << r.size() << endl << r << endl;
}