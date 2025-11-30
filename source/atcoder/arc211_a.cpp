// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int solve(vector<ll>& a) {
    set<ll> num_exists;
    for (int i = 1; i <= 9; i++) {
        if (a[i] > 0) {
            num_exists.insert(i);
        }
    }
    if (num_exists.size() == 0) {
        return 0;
    }
    else if (num_exists.size() == 1) {
        ll only_num = *num_exists.begin();
        if (only_num == 5) {
            return a[5] - 1;
        }
        else {
            return 0;
        }
    }
    else if (num_exists.size() == 2) {
        ll n1 = *num_exists.begin(), n2 = *(++num_exists.begin());
        if (n1 + n2 == 10) {
            return 1;
        }
        else if (n1 == 5) {
            return max(0ll, a[5] - a[n2] - 1);
        }
        else if (n2 == 5) {
            return max(0ll, a[5] - a[n1] - 1);
        }
        else {
            return 0;
        }
    }
    else {
        ll not_5_count = 0;
        for (int i = 1; i <= 9; i++) {
            if (i != 5) {
                not_5_count += a[i];
            }
        }
        return max(0ll, a[5] - not_5_count - 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while(t--) {
        vector<ll> a(10);
        for (int i = 1; i <= 9; i++) {
            cin >> a[i];
        }
        cout << solve(a) << "\n";
    }

    return 0;
}