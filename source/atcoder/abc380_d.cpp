#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

bool changed(ll n)
{
    // popcount
    ll cnt = 0;
    while (n > 0) {
        cnt += n & 1;
        n >>= 1;
    }
    return cnt % 2 == 1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s;
    cin >> s;
    int q;
    cin >> q;
    vector<char> ans;
    for (int i = 0; i < q; i++) {
        ll k;
        cin >> k;
        k--;
        ll period = k / s.length();
        ll rem = k % s.length();
        if (changed(period)) {
            // alter case
            if (s[rem] > 'Z') {
                ans.push_back((char)(s[rem] - 32));
            }
            else {
                ans.push_back((char)(s[rem] + 32));
            }
        }
        else {
            ans.push_back(s[rem]);
        }
    }

    for (auto elem : ans) {
        cout << elem << ' ';
    }

    return 0;
}

// q q W e t I E Q
// q q W e t I E Q
