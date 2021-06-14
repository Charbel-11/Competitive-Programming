#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

long long maxPoss = 4294967295;

int main() {
	int n;
	cin >> n;

	long long x = 0;
	bool ov = false;
	int curNested = 0;
	vector<long long> repTime(n + 1, 1);

	for (int i = 0; i < n; i++) {
		string line;
		cin >> line;

		if (curNested == 0 && line == "add") {
			x++;
			if (x > maxPoss) {
				ov = true;
			}
		}
		else if (line == "add") {
			if (repTime[curNested] == -2) {
				ov = true;
			}
			else {
				x += repTime[curNested];
				if (x > maxPoss) {
					ov = true;
				}
			}
		}
		else if (line == "end") {
			curNested--;
		}
		else if (line == "for") {
			int num;
			cin >> num;
			curNested++;
			if (repTime[curNested - 1] == -2) {
				repTime[curNested] = -2;
			}
			else {
				repTime[curNested] = num * repTime[curNested - 1];		//To avoid for loops !!
				if (repTime[curNested] > maxPoss) {					//So it has to be a long long vector
					repTime[curNested] = -2;
				}
			}
		}
	}

	if (ov) {
		cout << "OVERFLOW!!!" << endl;
		return 0;
	}
	cout << x << endl;
}