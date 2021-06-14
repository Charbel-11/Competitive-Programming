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

	while (a <= b) {
		if (a == b) {
			if (numbers[a] > lastEl) {
				r += 'L';
			}
			break;
		}

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
		else if (numbers[b] < numbers[a]) {
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

		//Key observation: taking the leftmost element means we will never take right anymore
		//So 2 cases are easily found without recursion
		else {
			if (numbers[a] <= lastEl) { break; }	//Need to make sure we can use one of them

			int c1 = 1;
			int tempA = a + 1;
			int tempLast = numbers[a];

			while (tempA<b && numbers[tempA]>tempLast) {
				tempLast = numbers[tempA];
				c1++;
				tempA++;
			}

			int c2 = 1;
			int tempB = b - 1;
			tempLast = numbers[b];

			while (tempB>a && numbers[tempB]>tempLast) {
				tempLast = numbers[tempB];
				c2++;
				tempB--;
			}

			if (c2 > c1)
			{
				for (int i = 0; i < c2; i++) {
					r += 'R';
				}
			}
			else {
				for (int i = 0; i < c1; i++) {
					r += 'L';
				}
			}

			break;		//No turning back
		}
	}

	cout << r.size() << endl << r << endl;
}