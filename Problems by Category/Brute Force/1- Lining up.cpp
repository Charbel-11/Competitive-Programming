#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

vector<pair<double, double>> points;

int maxPts() {
	map<pair<double, double>, int> freq;

	for (int i = 0; i < points.size(); i++) {
		for (int j = i + 1; j < points.size(); j++) {
			double slope = (points[j].second - points[i].second) / (points[j].first - points[i].first);
			double intercept = points[j].second - points[j].first*slope;

			if (freq.count({ slope, intercept }) == 0) {
				freq[{slope, intercept}] = 1;
			}
			else {
				freq[{slope, intercept}]++;
			}
		}
	}

	map<pair<double, double>, int>::iterator itr = freq.begin();
	map<pair<double, double>, int>::iterator max;

	int curMax = 0;

	while (itr != freq.end()) {
		if (itr->second > curMax) {
			curMax = itr->second;
			max = itr;
		}
		itr++;
	}

	int startCount = 1;
	bool begin = false;

	for (int i = 0; i < points.size(); i++) {
		for (int j = i + 1; j < points.size(); j++) {
			double slope = (points[j].second - points[i].second) / (points[j].first - points[i].first);
			double intercept = points[j].second - points[j].first*slope;

			if (slope == max->first.first && intercept == max->first.second) {
				begin = true;
				startCount++;
			}
		}
		if (begin) { break; }
	}

	return startCount;
}

int main() {
	int n; cin >> n;
	string s;
	getline(cin, s);
	getline(cin, s);

	for (int i = 0; i < n; i++) {
		points.clear();
		while (getline(cin, s) && !s.empty()) {
			string num1 = "";
			string num2 = "";
			int i = 0;
			while (s[i] != ' ') {
				num1.push_back(s[i]);
				i++;
			}
			i++;
			while (i < s.length()) {
				num2.push_back(s[i]);
				i++;
			}
			points.push_back({ stod(num1), stod(num2) });
		}
		cout << maxPts() << endl;
		if (i + 1 != n) { cout << endl; }
	}

	return 0;
}