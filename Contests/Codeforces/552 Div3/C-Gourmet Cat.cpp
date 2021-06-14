#include <iostream>
#include <string>

using namespace std;


int main() {
	int a, b, c;		//a for M-Th-Su   b for T-Sat	c for W-F
						//a for 0,3,6	  b for 1,5     c for 2,4
	cin >> a >> b >> c;

	//Try big inputs, then work smartly
	int sureDays = 0;
	while (a > 3 && b > 2 && c > 2) {
		a -= 3; b -= 2; c -= 2;
		sureDays += 7;
	}

	int maxDays = sureDays;
	for (int i = 0; i < 7; i++) {	//start day is 0
		int curA = a;
		int curB = b;
		int curC = c;

		int curAt = i;
		int curDays = sureDays;

		while (true) {
			if (curAt == 0 || curAt == 3 || curAt == 6) { curA--; }
			else if (curAt == 1 || curAt == 5) { curB--; }
			else { curC--; }

			if (curA >= 0 && curB >= 0 && curC >= 0) {
				curDays++;
				curAt = (curAt + 1) % 7;
			}
			else {
				break;
			}
		}
		if (curDays > maxDays) { maxDays = curDays; }
	}

	cout << maxDays << endl;
}