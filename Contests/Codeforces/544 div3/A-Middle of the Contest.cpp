#include <iostream>
#include <string>

using namespace std;

int main() {
	string i1, i2;
	cin >> i1 >> i2;

	string t1 = "";
	string t2 = "";
	if (i1[0] != '0')
		t1.push_back(i1[0]);			//use push_back not +
	t1.push_back(i1[1]);
	if (i1[3] != '0')
		t2.push_back(i1[3]);
	t2.push_back(i1[4]);

	int h1 = stoi(t1);
	int m1 = stoi(t2);

	t1 = ""; t2 = "";
	if (i2[0] != '0')
		t1.push_back(i2[0]);
	t1.push_back(i2[1]);
	if (i2[3] != '0')
		t2.push_back(i2[3]);
	t2.push_back(i2[4]);

	int h2 = stoi(t1);
	int m2 = stoi(t2);

	int startMin = m1 + h1 * 60;
	int endMin = m2 + h2 * 60;
	int half = (startMin + endMin) / 2;

	if (half / 60 < 10) {
		cout << "0" << half / 60;
	}
	else {
		cout << half / 60;
	}

	if (half % 60 < 10) {
		cout << ":0" << half % 60 << endl;
	}
	else {
		cout << ":" << half % 60 << endl;
	}
}