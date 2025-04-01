// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll solve(string l, string r)
{
    ll ans = 0;
    while (l.size() < r.size()) {
        l = '0' + l;
    }

    for (int i = 0; i < l.size(); i++) {
        if (l[i] == '8' && r[i] == '8') {
            ans++;
        }
        else if (l[i] != r[i]) {
            break;
        }
    }

    return ans;
}

ll naive(string l, string r)
{
    ll l_int = stoll(l);
    ll r_int = stoll(r);
    ll ans = l.size();
    for (int i = l_int; i <= r_int; i++) {
        string s = to_string(i);
        ans = min(ans, (ll)count(s.begin(), s.end(), '8'));
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef DEBUG
    for (int i = 1; i <= 1000; i++) {
        for (int j = i; j <= 1000; j++) {
            string l = to_string(i);
            string r = to_string(j);
            if (naive(l, r) != solve(l, r)) {
                cout << "Error: " << l << " " << r << endl;
                cout << naive(l, r) << " " << solve(l, r) << endl;
                return 1;
            }
        }
    }
#endif

    string l, r;
    cin >> l >> r;

    cout << solve(l, r) << endl;

    return 0;
}