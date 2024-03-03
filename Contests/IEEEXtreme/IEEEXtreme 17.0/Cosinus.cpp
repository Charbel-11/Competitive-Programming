#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ld PI = 3.14159265358979323;

// Reconstructs a fraction from a continued fraction with the given coefficients
pair<ll, ll> reconstructFraction(vector<ll>& coeff){
    ll numerator = coeff.back(),  denominator = 1;

    for(int i = coeff.size() - 2; i >= 0; --i) {
        swap(numerator, denominator);
        numerator += denominator * coeff[i];
    }
    return {numerator, denominator};
}

ll findSmallestInteger(ld input){
    ld eps = 0.0000001;
    double rem = input;
    vector<ll> coeff;
    while (true) {
        //calculate the next coefficient
        ll integer = (ll)(rem);
        rem -= integer; rem = 1 / rem;
        coeff.push_back(integer);

        auto reconstructed = reconstructFraction(coeff);
        ld multipliedInput = input * reconstructed.second;
        ld multipliedInputRounded = round(multipliedInput);
        if (abs(multipliedInput - multipliedInputRounded) < eps)
            return reconstructed.second;
    }
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

    int t; cin >> t;
    while(t--){
        ld alpha; cin >> alpha;
        ll ans = findSmallestInteger(90.0/alpha);
        cout << ans << '\n';
    }
}

