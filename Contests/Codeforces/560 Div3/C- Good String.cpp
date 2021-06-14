#include <string>
#include <iostream>

using namespace std;


int main() {
	int n;
	cin >> n;
	string word; 
	cin >> word;

	string res = "";
	int toDel = 0;
	
	int i = 0;
	for (; i < n - 1; i+=2) {
		if (word[i] != word[i + 1]) {
			res.push_back(word[i]);
			res.push_back(word[i + 1]);
		}
		else {
			//always either add 2 or nothing
			while (i < n - 1 && word[i] == word[i + 1]) {
				i++;
				toDel++;
			}
			if (i < n - 1) {
				res.push_back(word[i]);
				res.push_back(word[i + 1]);
			}
			else if (i == n - 1) { toDel++; }
		}
	}
	if (i == n - 1) { toDel++; }
/*
	// !!! Edge case !!! 
	if (n == 1) {
		toDel = 1;
	}
*/	
	cout << toDel << endl << res << endl;
}