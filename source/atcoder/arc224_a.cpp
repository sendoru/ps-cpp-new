// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

bool check(ll n) {
    string n_str = to_string(n);
    for (int i = 0; i < (ll)n_str.size() - 1; i++) {
        if (n_str[i] == '0' && n_str[i + 1] == '0') {
            return true;
        }
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        for (int i = 1; i <= 100; i++) {
            if (check(n * i)) {
                cout << n * i << "\n";
                break;
            }
        }
    }

    return 0;
}