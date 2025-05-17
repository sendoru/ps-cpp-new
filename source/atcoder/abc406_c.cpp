// #include "atcoder/all"
// #define DEBUG
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll solve(vector<ll> &p)
{
    ll n = p.size();
    vector<ll> diff(n - 1);
    for (int i = 0; i < n - 1; i++) {
        diff[i] = p[i + 1] - p[i] > 0 ? 1 : -1;
    }

    vector<pll> group;
    group.push_back({diff[0], 1});
    for (int i = 1; i < n - 1; i++) {
        if (diff[i] == group.back().first) {
            group.back().second++;
        }
        else {
            group.push_back({diff[i], 1});
        }
    }

    ll ans = 0;

    for (int i = 0; i < group.size(); i++) {
        if (i + 2 < group.size() && group[i].first == 1) {
            ans += group[i].second * group[i + 2].second;
        }
    }

    return ans;
}

bool is_good(vector<ll> &v)
{
    if (v.size() < 4) {
        return false;
    }
    if (v[0] >= v[1]) {
        return false;
    }
    ll local_max_cnt = 0, local_min_cnt = 0;
    for (int i = 1; i < (int)v.size() - 1; i++) {
        if (v[i] > v[i - 1] && v[i] > v[i + 1]) {
            local_max_cnt++;
        }
        else if (v[i] < v[i - 1] && v[i] < v[i + 1]) {
            local_min_cnt++;
        }
    }

    return local_max_cnt == 1 && local_min_cnt == 1;
}

ll solve_naive(vector<ll> &p)
{
    ll n = p.size();
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            vector<ll> v;
            for (int k = i; k <= j; k++) {
                v.push_back(p[k]);
            }
            if (is_good(v)) {
                ans++;
            }
        }
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef DEBUG
    ll tc_count = 50;
    while (tc_count--) {
        ll n = 50;
        vector<ll> p(n);
        iota(p.begin(), p.end(), 1);
        random_shuffle(p.begin(), p.end());
        ll ans = solve(p), ans_naive = solve_naive(p);
        if (ans != ans_naive) {
            cout << "Fail: " << ans << ' ' << ans_naive << '\n';
            cout << "p: ";
            for (auto x : p) {
                cout << x << ' ';
            }
            cout << '\n';
            return 0;
        }
    }
    // cout << "Pass" << endl;
#endif

    ll n;
    cin >> n;
    vector<ll> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    ll ans = solve(p);

    cout << ans << '\n';

    return 0;
}