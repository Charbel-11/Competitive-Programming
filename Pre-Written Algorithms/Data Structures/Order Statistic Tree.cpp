#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ORDER STATISTIC TREE
// insert(x): insert element x
// find_by_order(k): Returns an iterator to the k-th element (0-based, use * to dereference)
// erase(k): Erases elements with value k
// order_of_key(k): Returns the "index" of some value k. If it is not in the set, then returns 0
// (it also returns 0 for the min, so we need to check if the element is in the set using .find() to distinguish)
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>	 // Including tree_order_statistics_node_update
using namespace __gnu_pbds;
typedef tree<ll, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
// We can change ll to anything like pair or vector if needed

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

    ordered_set X;
    X.insert(1);
    X.insert(2);
    X.insert(4);
    X.insert(8);
    X.insert(16);

    cout<<*X.find_by_order(1)<<endl; // 2
    cout<<*X.find_by_order(2)<<endl; // 4
    cout<<*X.find_by_order(4)<<endl; // 16
    cout<<(X.end()==X.find_by_order(6))<<endl; // true

    cout << (X.find(-5) == X.end()) << " " << X.order_of_key(-5)<<endl;  // 1 0
    cout<<X.order_of_key(1)<<endl;   // 0
    cout<<X.order_of_key(3)<<endl;   // 2
    cout<<X.order_of_key(4)<<endl;   // 2
    cout<<X.order_of_key(400)<<endl; // 5
}