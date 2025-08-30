// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    string s;
    cin >> s;
    string goal = s;
    vector<int> a_idx;
    for (int i = 0; i < 2 * n; i++) {
        if (s[i] == 'A') {
            a_idx.push_back(i);
        }
    }

    ll min1 = 0, min2 = 0;
    for (int i = 0; i < n; i++) {
        min1 += abs(2 * i - a_idx[i]);
        min2 += abs(2 * i + 1 - a_idx[i]);
    }

    cout << min(min1, min2) << "\n";

    return 0;
}