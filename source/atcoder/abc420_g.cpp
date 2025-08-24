// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<ll> solve_naive(ll x) {
    vector<ll> ans;
    for (__int128_t i = -abs(x) - 5; i <= abs(x) + 5; i++) {
        __int128_t val = i * i + i + x;
        if (val < 0) {
            continue;
        }
        __int128_t sq = (__int128_t)sqrt((long double)val);
        if (sq * sq == val) {
            ans.push_back(i);
        }
    }
    return ans;
}

vector<ll> solve(ll x) {
    ll xx = 4 * x - 1;
    vector<ll> ans;

    for (ll i = 1; i * i <= abs(xx); i++) {
        if (xx % i != 0) {
            continue;
        }
        ll j = xx / i;
        if ((i + j) % 4 == 0 && (j - i - 2) % 4 == 0) {
            ans.push_back((j - i - 2) / 4);
        }
        ll ni = -i, nj = -j;
        if ((ni + nj) % 4 == 0 && (nj - ni - 2) % 4 == 0) {
            ans.push_back((nj - ni - 2) / 4);
        }
        ni = j, nj = i;
        if ((ni + nj) % 4 == 0 && (nj - ni - 2) % 4 == 0) {
            ans.push_back((nj - ni - 2) / 4);
        }
        ni = -j, nj = -i;
        if ((ni + nj) % 4 == 0 && (nj - ni - 2) % 4 == 0) {
            ans.push_back((nj - ni - 2) / 4);
        }
    }
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll x;
    cin >> x;

    vector<ll> ans = solve(x);
    cout << ans.size() << '\n';
    for (ll v : ans) {
        cout << v << ' ';
    }

    return 0;
}