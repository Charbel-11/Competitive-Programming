//careful references in recursion
// careful copying when doing vectors esp in loops and funcrions
// walaw base cases
//careful long long int and mod always OMG
//careful return types of std such as int(ceil)
//io manip lookup for decimal control
//WATCH OUT GOING OVER MAX thru operations spam mod
// vectors overflow arrays do NOT
//cout endl lol
//lower bound is first greater or equal
//uper is first greater
// if TLE play around with compiler
// use static is helpful!!
//take note of test stuff that need to be changed before submission
// careful when u use garbage from abroad
// modeling stuff as num going below 0 above n
// number theory infinite due to multple of each other
//careful not finding stuff in dictionaries
//stupid cout precision and sci notations
// set rbegin() or --end() for last
//careful multiset removal just use  heapp
// no segment trees if partial mins are needed
// in combinatorics log matters esp in that dp, and think v carefully
#include<bits/stdc++.h>
using namespace std;

//macros and shortcuts
#define loop(i, n) for(int i = 0; i < n; i++)
#define pool(i, n) for(int i = n-1; i >=0; i--)
#define loopy(i, o, n) for(int i = o; i < n; i++)
#define pooly(i, o, n) for(int i = o-1; i >= n; i--)

#define scan(it, d) for(auto it=d.begin(); it!=d.end(); it++)

typedef long long ll; //can be modified to long/int in emergencies.
typedef long long lll;

const int maxint = 2147483646;
const int minint = -2147483646;
const lll maxlll = 9223372036854775805;
const lll minlll = -9223372036854775805;
const ll mody = 998244353;

// here lie the output functions
template<class T>
ostream& operator<<(ostream& os, vector<T> v) {
	os << "[";
	for (int i = 0; i < v.size(); i++) {
		os << v[i];
		if (i != v.size() - 1) {
			os << ", ";
		}
	}
	os << "]";
	//cout<<endl;
	return os;
}
template<class T, class U>
ostream& operator<<(ostream& os, unordered_map<T, U> dt) {
	os << "{";
	for (auto i = dt.begin(); i != dt.end(); i++) {
		os << i->first << ": " << i->second;
		auto temp = i;
		temp++;
		if (temp != dt.end()) {
			os << ", ";
		}
	}
	os << "}";
	//os<<endl;
	return os;
}
template<class T, class U>
ostream& operator<<(ostream& os, pair<T, U> dt) {
	os << "(" << dt.first << "," << dt.second << ")";
	return os;
}
template <typename T, unsigned int N>
typename std::enable_if<!std::is_same<T, char>::value, std::ostream &>::type
operator<<(std::ostream & os, const T(&a)[N]) {
	for (size_t i = 0; i < N; ++i)
	{
		os << a[i];
		if (i < N - 1) {
			cout << " ";
		}
	}
	os << endl;
	return os;
}


// less useful prints note that stack and queue modify the info and put it back whereas pq takes nlogn

template<class T, class U>
ostream& operator<<(ostream& os, map<T, U> dt) {
	os << "{";
	for (auto i = dt.begin(); i != dt.end(); i++) {
		os << i->first << ": " << i->second;
		auto temp = i;
		temp++;
		if (temp != dt.end()) {
			os << ", ";
		}
	}
	os << "}";
	//os<<endl;
	return os;
}
template<class T, class U>
ostream& operator<<(ostream& os, multimap<T, U> dt) {
	os << "{";
	for (auto i = dt.begin(); i != dt.end(); i++) {
		os << i->first << ": " << i->second;
		auto temp = i;
		temp++;
		if (temp != dt.end()) {
			os << ", ";
		}
	}
	os << "}";
	//os<<endl;
	return os;
}
template<class T>
ostream& operator<<(ostream& os, set<T> dt) {
	os << "{";
	for (auto i = dt.begin(); i != dt.end(); i++) {
		os << *i;
		auto temp = i;
		temp++;
		if (temp != dt.end()) {
			os << ", ";
		}
	}
	os << "}";
	//os<<endl;
	return os;
}
template<class T>
ostream& operator<<(ostream& os, multiset<T> dt) {
	os << "{";
	for (auto i = dt.begin(); i != dt.end(); i++) {
		os << *i;
		auto temp = i;
		temp++;
		if (temp != dt.end()) {
			os << ", ";
		}
	}
	os << "}";
	//os<<endl;
	return os;
}
template<class T>
ostream& operator<<(ostream& os, stack<T> dt) {
	stack<T> t;
	os << "[";
	while (!dt.empty()) {
		T temp = dt.top();
		os << temp;
		dt.pop();
		t.push(temp);
		if (!dt.empty()) {
			os << ", ";
		}
	}
	os << "]";
	while (!t.empty()) {
		T temp = t.top();
		dt.push(temp);
		t.pop();
	}
	//os<<endl;
	return os;
}
template<class T>
ostream& operator<<(ostream& os, queue<T> dt) {
	queue<T> t;
	os << "[";
	while (!dt.empty()) {
		T temp = dt.front();
		os << temp;
		dt.pop();
		t.push(temp);
		if (!dt.empty()) {
			os << ", ";
		}
	}
	os << "]";
	while (!t.empty()) {
		T temp = t.front();
		dt.push(temp);
		t.pop();
	}
	//os<<endl;
	return os;
}
template<class T>
ostream& operator<<(ostream& os, list<T> dt) {
	os << "[";
	for (auto i = dt.begin(); i != dt.end(); i++) {
		os << *i;
		auto temp = i;
		temp++;
		if (temp != dt.end()) {
			os << ", ";
		}
	}
	os << "]";
	//os<<endl;
	return os;
}
template<class T>
ostream& operator<<(ostream& os, priority_queue<T> dt) {
	queue<T> t;
	os << "[";
	while (!dt.empty()) {
		T temp = dt.top();
		os << temp;
		dt.pop();
		t.push(temp);
		if (!dt.empty()) {
			os << ", ";
		}
	}
	os << "]";
	while (!t.empty()) {
		T temp = t.front();
		dt.push(temp);
		t.pop();
	}
	//os<<endl;
	return os;
}
//here lie the input functions
template <class T = ll>
vector<T> clist(int n) {
	std::vector<T> v;
	while (n--) {
		T k;
		cin >> k;
		v.push_back(k);
	}
	return v;
}
template<class T = ll, class U = ll>
vector<pair<T, U>> clist2(int n) {
	std::vector<pair<T, U>> v;
	while (n--) {
		T a;
		U b;
		cin >> a >> b;
		pair<T, U> p(a, b);
		v.push_back(p);
	}
	return v;
}

template <class T = ll>
vector<pair<T, int>> clistind(int n) {
	std::vector<pair<T, int>> v;
	loop(i, n) {
		T k;
		cin >> k;
		pair<T, int> p(k, i);
		v.push_back(p);
	}
	return v;
}
template<class T = ll, class U = ll>
vector<pair<pair<T, U>, int>> clist2ind(int n) {
	std::vector<pair<pair<T, U>, int>> v;
	loop(i, n) {
		T a;
		U b;
		cin >> a >> b;
		pair<T, U> p(a, b);
		pair<pair<T, U>, int> pp(p, i);
		v.push_back(pp);
	}
	return v;
}
// this is a special string to vector function
vector<char> cstrtv(string& s) {
	vector<char> v;
	for (int i = 0; i < s.size(); i++) {
		v.push_back(s[i]);
	}
	return v;
}

//turn arrays and strings into frequencies

template<class T>
struct freq {
	//can be turned to set for modifiable acces
	//features:
	//use freq iterators to go over all of m
	//keys of m can directly access freq using []
	//keys can find first and last positions with functions

	// key to array requires call on M
	map<T, vector<int>>m; //can support acess on empty by auto creating an empty vector
	int n;
	freq(vector<T>& s) {
		n = s.size();
		for (int i = 0; i < s.size(); i++) {
			if (m.find(s[i]) == m.end()) {
				vector<int> v;
				m[s[i]] = v;
			}
			m[s[i]].push_back(i);
		}
	}
	freq(string& s) {
		n = s.size();
		for (int i = 0; i < s.size(); i++) {
			if (m.find(s[i]) == m.end()) {
				vector<int> v;
				m[s[i]] = v;
			}
			m[s[i]].push_back(i);
		}
	}
	typename map<T, vector<int>>::iterator begin() {
		return m.begin();
	}
	typename map<T, vector<int>>::iterator end() {
		return m.end();
	}
	int operator[] (T ind) { //supports empty and nulls
		if (m.find(ind) == m.end()) {
			return 0;
		}
		return m[ind].size();
	}
	T mode() { //do not call on empty
		int maxfrq = 0;
		T maxel;
		for (auto it = m.begin(); it != m.end(); it++) {
			if (it->second.size() > maxfrq) {
				maxfrq = it->second.size();
				maxel = it->first;
			}
		}
		return maxel;
	}
	int first(T el) {
		if (m[el].size() != 0) {
			return m[el][0];
		}
		return n;
	}
	int last(T el) {
		if (m[el].size() != 0) {
			return m[el][m[el].size() - 1];
		}
		return -1;
	}
	bool equals(freq<T>& o) {
		for (auto it = begin(); it != end(); it++) {
			if ((*this)[it->first] != o[it->first]) {
				return false;

			}
		}
		for (auto it = o.begin(); it != o.end(); it++) {
			if ((*this)[it->first] != o[it->first]) {
				return false;
			}
		}
		return true;
	}
};


//here lie common vector processing functions
template<class T>
int maxind(vector<T>& v) {
	int maxi = 0;
	for (int i = 1; i < v.size(); i++) {
		maxi = (v[maxi] < v[i]) ? i : maxi;
	}
	return maxi;
}
template<class T>
T maxel(vector<T>& v) {
	return v[maxind(v)];
}
template<class T>
int minind(vector<T>& v) {
	int mini = 0;
	for (int i = 1; i < v.size(); i++) {
		mini = (v[mini] > v[i]) ? i : mini;
	}
	return mini;
}
template<class T>
T minel(vector<T>& v) {
	return v[minind(v)];
}
template<class T>
vector<ll> partialsums(vector<T>& v) {
	vector<ll> ps(v.size());
	ps[0] = v[0];
	for (int i = 1; i < v.size(); i++) {
		ps[i] = ps[i - 1] + v[i];
	}
	return ps;
}
template<class T>
ll sumy(vector<T>& v) {
	ll s = 0;
	for (int i = 0; i < v.size(); i++) {
		s += v[i];
	}
	return s;
}
template<class T>
vector<int> pminin(vector<T>& v) {
	vector<int> ret = { 0 };
	int curi = 0;
	for (int i = 1; i < v.size(); i++) {
		if (v[i] < v[curi]) {
			curi = i;

		}
		ret.push_back(curi);
	}
	return ret;
}
template<class T>
vector<int> pmaxin(vector<T>& v) {
	vector<int> ret = { 0 };
	int curi = 0;
	for (int i = 1; i < v.size(); i++) {
		if (v[i] > v[curi]) {
			curi = i;

		}
		ret.push_back(curi);
	}
	return ret;
}
template<class T>
vector<T> pmin(vector<T>& v) {
	vector<T> ret;
	vector<int> temp = pminin(v);
	for (int i = 0; i < temp.size(); i++) {
		ret.push_back(v[temp[i]]);
	}
	return ret;
}
template<class T>
vector<T> pmax(vector<T>& v) {
	vector<T> ret;
	vector<int> temp = pmaxin(v);
	for (int i = 0; i < temp.size(); i++) {
		ret.push_back(v[temp[i]]);
	}
	return ret;
}

// accessing operators in circular shiz
int ind(int i, int n) {
	if (i%n >= 0) {
		return i % n;
	}
	return (i%n) + n;
}


ll modsub(ll a, ll b) {
	ll ans = a % mody - b % mody;
	if (ans < 0) {
		return ans + mody;
	}
	return ans;
}
ll gcdExtended(ll a, ll b, ll *x, ll *y);

// Function to find modulo inverse of a
ll modinv(ll a) {
	ll m = mody;
	ll x, y;
	ll g = gcdExtended(a, m, &x, &y);
	ll res = (x%m + m) % m;
	return res;
}

// C function for extended Euclidean Algorithm
ll gcdExtended(ll a, ll b, ll *x, ll *y) {
	// Base Case
	if (a == 0) {
		*x = 0, *y = 1;
		return b;
	}
	ll x1, y1; // To store results of recursive call
	ll gcd = gcdExtended(b%a, a, &x1, &y1);
	// Update x and y using results of recursive
	// call
	*x = y1 - (b / a) * x1;
	*y = x1;
	return gcd;
}


// NUMBER THEORY
template<class T = ll>
set<T> divisors(T n) {
	set<T> s;
	for (int i = 1; i <= sqrt(n); i++) {
		if (n%i == 0) {
			// If divisors are equal, print only one
			if (n / i == i) {
				s.insert(i);
			}
			else { // Otherwise print both
				s.insert(i);
				s.insert(n / i);
			}
		}
	}
	return s;
}
template<class T = ll>
freq<T> pf(T n) {
	vector<T> s;
	// Print the number of 2s that divide n
	while (n % 2 == 0) {
		s.push_back(2);
		n = n / 2;
	}
	// n must be odd at this point. So we can skip
	// one element (Note i = i +2)
	for (T i = 3; i <= sqrt(n); i = i + 2) {
		// While i divides n, print i and divide n
		while (n % i == 0) {
			s.push_back(i);
			n = n / i;
		}
	}
	// This condition is to handle the case when n
	// is a prime number greater than 2
	if (n > 2) {
		s.push_back(n);
	}
	return freq<T>(s);
}

//set to n+1
bool isprime[1];
void seive(int n) {
	loop(i, n + 1) {
		isprime[i] = true;;
	}
	isprime[0] = false;
	isprime[1] = false;
	loop(i, n + 1) {
		if (isprime[i]) {
			for (int j = 2 * i; j < n + 1; j += i) {
				isprime[j] = false;
			}
		}
	}
}

ll modexp(ll n, ll e) {
	if (e == 0) {
		return 1;
	}
	else {
		if (e % 2) {
			return (n*(modexp(n, e - 1))) % mody;
		}
		else {
			ll res = modexp(n, e / 2);
			return (res*res) % mody;
		}
	}
}

// binary stuff

int countbits(ll n) {
	ll count = 0;
	while (n) {
		count += n & 1;
		n >>= 1;
	}
	return count;
}

string bts(ll n, int p) {
	string s = "";
	loop(i, p) {
		s.push_back('0');
	}
	loop(i, p) {
		if (n % 2) {
			s[p - i - 1] = '1';
		}
		n /= 2;
	}
	return s;
}


void binarysearch() {
	//rg is the first false
	// lf is last true

	/*int lf = 0;
	int rg = n;
	while (rg - lf > 1) {
		int mid = (lf + rg) / 2;
		if(calc(p, mid, x, a, y, b)){
			lf = mid;
		}
		else{
			rg = mid
		}
	} */
}


//comBINATORICS:

ll comb[1][1]; //set to max n+1 and fix the array
ll choose(int n, int r) {
	if (comb[n][r] != -1) {
		return comb[n][r];
	}
	if (r == n) {
		return 1;
	}
	if (r == 0) {
		return 1;
	}
	comb[n][r] = (choose(n - 1, r - 1) + choose(n - 1, r)) % (mody);
	return comb[n][r];
}

//factorial
ll factorial[1]; //set to n+1 and fix the array
ll fact(int n) {
	if (n == 0) {
		return 1;
	}
	if (factorial[n] != -1) {
		return factorial[n];
	}
	else {
		factorial[n] = (n*fact(n - 1)) % mody;
		return factorial[n];
	}
}
// point and its functions and input


struct point {
	ll a;
	ll b;
	ll c;
	point(ll aa, ll bb, ll cc) : a(aa), b(bb), c(cc) {}

};
ostream& operator<<(ostream& os, point p) {
	os << "(" << p.a << ", " << p.b << ", " << p.c << ")";
	return os;
}
bool operator<(const point &a, const point &b)
{
	if (a.a == b.a) {
		if (a.b == b.b) {
			return a.c < b.c;
		}
		return a.b < b.b;
	}
	return a.a < b.a;
}
vector<point> clist3(int n) {
	std::vector<point> v;
	while (n--) {
		ll a, b, c;
		cin >> a >> b >> c;
		point p(a, b, c);
		v.push_back(p);
	}
	return v;
}
vector<pair<point, int>> clist3ind(int n) {
	std::vector<pair<point, int>> v;
	loop(i, n) {
		ll a, b, c;
		cin >> a >> b >> c;
		point p(a, b, c);
		pair<point, int> pp(p, i);
		v.push_back(pp);
	}
	return v;
}
template<class T>
vector<int> islets(vector<T>& v) {
	vector<int> ret;
	int cur = 1;
	loopy(i, 1, v.size()) {
		if (v[i] == v[i - 1]) {
			cur++;
		}
		else {
			ret.push_back(cur);
			cur = 1;
		}
	}
	ret.push_back(cur);
	return ret;
}

struct node;
struct edge;
struct node {
	int pos;
	int tag = 0;
	vector<edge> edges;
	node(int valy) : pos(valy) {}
	node(int valy, int taggy) : pos(valy), tag(taggy) {}
	void add(edge &e) {
		edges.push_back(e);
	}
	//to do add constructor, cout
};
struct edge {
	node* source;
	node* dest;
	int weight = 0;
	// consider making it by pointer of indeces here
	edge(node* sourcey, node* desty) : source(sourcey), dest(desty) {}
	edge(node* sourcey, node* desty, int valy) : source(sourcey), dest(desty), weight(valy) {}
	// to do add constructor, cout
};
struct graph {
	// all processing is done by node indeces to avoid copying nodes, and that is called pos in the node, nodes are uncopyiable edges are, so far. graph is relatively static
	vector<node> nodes;
	bool d;
	graph(int sz, int dd = 0) {
		d = dd;
		loop(i, sz) {
			node v(i);
			nodes.push_back(v);
		}
	}
	void addnode(int taggy = 0) {
		node v(nodes.size(), taggy);
		nodes.push_back(v);
	}
	void addedge(int source, int dest, int weight = 0) {
		node& so = nodes[source];
		node& de = nodes[dest];
		edge e(&so, &de, weight);
		nodes[source].add(e);
		if (d == 0) {
			edge ee(&de, &so, weight);
			nodes[dest].add(ee);
		}
	}
	vector<int> dfs() {
		// cannot have 0 nodes
		vector<int> parent(nodes.size(), -1);
		loop(i, nodes.size()) {
			if (parent[i] == -1) {
				stack<int> s;
				s.push(i);
				parent[i] = i;
				while (!s.empty()) {
					int cur = s.top();
					//cout<<cur<<endl;
					s.pop();
					loop(i, nodes[cur].edges.size()) {
						if (parent[nodes[cur].edges[i].dest->pos] == -1) {
							s.push(nodes[cur].edges[i].dest->pos);
							parent[nodes[cur].edges[i].dest->pos] = cur;
						}
					}
				}
			}
		}
		return parent;
	}
	vector<int> dfscomp() {
		// cannot have 0 nodes
		vector<int> parent(nodes.size(), -1);
		loop(i, nodes.size()) {
			if (parent[i] == -1) {
				stack<int> s;
				s.push(i);
				parent[i] = i;
				int pa = i;
				while (!s.empty()) {
					int cur = s.top();
					//cout<<cur<<endl;
					s.pop();
					loop(i, nodes[cur].edges.size()) {
						if (parent[nodes[cur].edges[i].dest->pos] == -1) {
							s.push(nodes[cur].edges[i].dest->pos);
							parent[nodes[cur].edges[i].dest->pos] = pa;
						}
					}
				}
			}
		}
		return parent;
	}
};
ostream& operator<<(ostream& os, graph g) {
	os << "{";
	loop(i, g.nodes.size()) {
		os << g.nodes[i].pos << ":[";
		loop(j, g.nodes[i].edges.size()) {
			os << g.nodes[i].edges[j].dest->pos << "(" << g.nodes[i].edges[j].weight << "), ";
		}
		os << "]" << endl;
	}
	os << "}";
	return os;
}
map<ll, vector<int>> intervalin(int n) {
	map<ll, vector<int>> m;
	loop(i, n) {
		ll a, b;
		cin >> a >> b;
		m[a].push_back(-i - 1);
		m[b].push_back(i + 1);
	}
	scan(it, m) {
		sort(it->second.begin(), it->second.end());
	}
	return m;
}
// td: fix cout stack queue no ref and order, REVISE CLIST OF VECT, cin pair, point
//count while clisting? cin matrix? and class?
//overload CIN??
// extends isets?
//clog?
// set variable to avoid having to fix and decalre?
//check initial values of vex, sets arays
//dfsi and a more dynamic graph
//add that it helps to have defined meanings for auxliary vars
//swap pair in vec?
long double f(long double n, long double k, long double i) {
	return(i / (i - 1)*(n + i - k) / (n + i));
}
long double f2(long double n, long double k, long double i) {
	if (i <= 0) {
		return -1;
	}
	long double ans = (k / (n - k + 1))*i;
	loop(j, i) {
		ans /= (n + i - j);
		ans *= (n - k + i - j);
	}
	return ans;
}
int main() {

	//std::ios::sync_with_stdio(0);
	//std::cin.tie(0);
	//std::cout.tie(0);
	long double n, k;
	cin >> n >> k;
	int lf = 0;
	int rg = 2 * n + 1;
	//loop(i,10){
	//    cout<<f(n,k,i)<<" ";
	//    cout<<f2(n,k,i)<<endl;
	//}
	while (rg - lf > 1) {
		int mid = (lf + rg) / 2;
		if (f(n, k, mid) >= 1) {
			lf = mid;
		}
		else {
			rg = mid;
		}
	}
	cout << setprecision(10) << f2(n, k, lf) << endl;
}
