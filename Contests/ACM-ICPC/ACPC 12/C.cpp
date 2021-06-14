#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
	string encS, s; cin >> encS >> s;
	map<char, int> freq;

	int stillNeeded = 0;
	for (int i = 0; i < s.size(); i++) {
		if (freq[s[i]] == 0) { stillNeeded++; }
		freq[s[i]]++;
	}

	for (int i = 0; i < s.size(); i++) {
		freq[encS[i]]--;
		if (freq[encS[i]] == 0) { stillNeeded--; }
	}
	for (int i = s.size(); i < encS.size(); i++) {
		if (stillNeeded == 0) { break; }

		freq[encS[i - s.size()]]++;
		if (freq[encS[i - s.size()]] == 1) { stillNeeded++; }
		freq[encS[i]]--;
		if (freq[encS[i]] == 0) { stillNeeded--; }

		if (stillNeeded == 0) { break; }
	}

	cout << ((stillNeeded == 0) ? "YES" : "NO") << endl;
}