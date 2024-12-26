// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct comp {
    bool operator()(const pll &a, const pll &b)
    {
        ll a_diff = a.second - a.first;
        ll b_diff = b.second - b.first;
        if (a_diff == b_diff) {
            return a.first < b.first;
        }
        return a_diff < b_diff;
    }
};

void print_ans(int t, ll a, ll b)
{
    cout << "Case #" << t << ": " << a << " " << b << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        ll n, k;
        cin >> n >> k;
        map<ll, ll> m;
        m[n + 1] = 1;
        while (k > 0) {
            auto it = prev(m.end());
            ll len = it->first;
            ll cnt = it->second;
            m.erase(it);
            ll a = len / 2;
            ll b = (len + 1) / 2;
            m[a] += cnt;
            m[b] += cnt;
            k -= cnt;
            if (k <= 0) {
                print_ans(t, b - 1, a - 1);
            }
        }
    }

    return 0;
}