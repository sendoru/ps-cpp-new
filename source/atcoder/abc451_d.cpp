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

    ll n;
    cin >> n;

    vector<ll> pow_2 = {1};
    do {
        pow_2.push_back(pow_2.back() * 2);
    } while (pow_2.back() <= 1e9);
    vector<ll> digit(pow_2.size());
    for (int i = 0; i < pow_2.size(); i++) {
        digit[i] = to_string(pow_2[i]).size();
        digit[i] = pow(10, digit[i]);
    }

    vector<ll> good;

    function<void(ll)> dfs = [&](ll x) {
        good.push_back(x);
        for (int i = 0; i < pow_2.size(); i++) {
            ll nxt = x * digit[i] + pow_2[i];
            if (nxt <= 1e9) {
                dfs(nxt);
            }
        }
    };

    dfs(0);
    sort(good.begin(), good.end());
    good.erase(unique(good.begin(), good.end()), good.end());

    cout << good[n];

    return 0;
}