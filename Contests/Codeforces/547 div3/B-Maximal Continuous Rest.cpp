#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> days(n);
	for (int i = 0; i < n; i++) {
		cin >> days[i];
	}
	for (int i = 0; i < n; i++) {		
		days.push_back(days[i]);				//When there is rotation, just add the same part in the end
	}

	int maxCons = 0;
	for (int i = 0; i < days.size()-1; i++) {			//for 0 1, we would have skipped the last element without normalizing 0 1 0 1
		int curCons = 0;								//We should have checked for the last element
		if (days[i] == 1) {
			curCons++;
			while (i < days.size()-1 && days[i + 1] == days[i]) {
				curCons++;
				i++;
			}
			if (curCons > maxCons) {
				maxCons = curCons;
			}
		}
	}
	cout << maxCons << endl;
}