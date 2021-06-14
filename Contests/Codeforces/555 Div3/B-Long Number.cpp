#include <iostream>
#include <string>
#include <vector>

using namespace std;


int main() {
	int n;
	cin >> n;
	string number;
	cin >> number;

	vector<int> f(9);
	for (int i = 0; i < 9; i++) {
		cin >> f[i];
	}

	bool started = false;

	for (int i = 0; i < n; i++) {
		int curNum = number[i] - '0';		//char to int gives ascii so -'0'
											//the opposite way requires +'0'

		if (curNum < f[curNum - 1]) {		//We start when we get a strictly bigger number
			cout << f[curNum - 1];		
			started = true;
			continue;
		}
		if (!started || curNum == f[curNum-1]) {
			cout << number[i];
		}
		else {							//started and found curNum > f[curNum-1]
			while (i < n) {				//because transformations should be contiguous
				cout << number[i];
				i++;
			}
		}
	}
	cout << endl;
}