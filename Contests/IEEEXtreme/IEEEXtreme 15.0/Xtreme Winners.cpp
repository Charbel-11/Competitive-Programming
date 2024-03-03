#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

map<string, int> m = { {"Team 1", 1}, {"Knapsackers@UNT", 2}, {"MoraSeekers", 3}, {"SurpriseTeam", 4}, {"CuSAT", 5},
	{"DongskarPedongi", 6}, {"cofrades", 7}, {"viRUs", 8}, {"TeamName", 9}, {"TeamEPFL1", 10}, {"whatevs", 11}, {"WildCornAncestors", 12},
	{"TheCornInTheFields", 13}, {"Aurora", 14} };

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string s; cin >> s;
	if (s == "Team") { cin >> s; cout << 1 << '\n'; }
	else { cout << m[s] << '\n'; }
}