#include <string>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

set<string> separator = { ".", ",", ":", ";", "!", "?" };
set<string> known; vector<string> cur; vector<string> originalCur;
int n;

void lowerC(string& s) {
	for (auto &c : s) { c = tolower(c); }
}

void addSentence() {
	for (int i = 0; i < cur.size(); i++) { lowerC(cur[i]); }

	for (int i = 0; i < cur.size(); i++) {
		string res = cur[i]; known.insert(res);
		for (int j = 1; j < n; j++) {
			if (i + j >= cur.size()) { break; }
			res += " " + cur[i + j]; known.insert(res);
		}
	}

	cur.clear(); originalCur.clear();
}

void checkSentence() {
	for (int i = 0; i < cur.size(); i++) {
		lowerC(cur[i]); string word = cur[i];
		if (known.count(word) == 0) { cout << "What does the word " << "\"" << originalCur[i] << "\"" << " mean?" << endl; }
		known.insert(word);
	}

	bool OK = true;
	for (int i = 0; i < cur.size(); i++) {
		string words = cur[i]; 
		for (int j = 1; j < n; j++) {
			if (i + j >= cur.size()) { break; }
			words += " " + cur[i + j];
			if (known.count(words) == 0) { OK = false; break; }
		}
		if (!OK) { break; }
	}

	if (!OK) {
		cout << "What does the sentence " << "\"";
		for (int i = 0; i < cur.size() - 1; i++) { cout << originalCur[i] << " "; }
		cout << originalCur.back() << "\"" << " mean?" << endl;

		addSentence();
	}
	else { cur.clear(); originalCur.clear(); }
}

int main() {
	int c = 1;
	string s = "";
	while (true) {
		if (s[0] == '#' && s.size() > 1) { n = s[1] - '0'; }
		else { cin >> n; if (cin.fail()) { break; } }
		if (c > 1) { cout << endl; }
		cout << "Learning case " << c++ << endl;

		known.clear();	known.insert("joe");

		cin >> s;
		while (s != "*") {
			if (separator.count(s) == 0) { cur.push_back(s); }
			else { addSentence(); }
			cin >> s;
		}
		if (cur.size() != 0) { addSentence(); }
		
		cin >> s; if (cin.fail()) { break; }
		while (s[0] != '#') {
			if (separator.count(s) == 0) { cur.push_back(s); originalCur.push_back(s); }
			else { checkSentence(); }
			cin >> s;
		}
		if (cur.size() != 0) { checkSentence(); }
	}
}