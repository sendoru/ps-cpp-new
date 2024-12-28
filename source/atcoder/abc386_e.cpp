// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<vector<int>> get_sorted_perm(ll n, ll k)
{
    vector<vector<int>> ret;
    vector<int> temp;

    function<void(int)> dfs = [&](int x) {
        if (temp.size() == k) {
            ret.push_back(temp);
            return;
        }
        for (int i = x; i < n; i++) {
            temp.push_back(i);
            dfs(i + 1);
            temp.pop_back();
        }
    };

    dfs(0);
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<int>> perms = get_sorted_perm(n, min(k, n - k));

    ll ans = 0;
    ll all_xor_sum = 0;
    for (int i = 0; i < n; i++) {
        all_xor_sum ^= a[i];
    }
    for (auto &perm : perms) {
        ll xor_sum = 0;
        for (auto &idx : perm) {
            xor_sum ^= a[idx];
        }
        if (k < n - k) {
            ans = max(ans, xor_sum);
        }
        else {
            ans = max(ans, all_xor_sum ^ xor_sum);
        }
    }

    cout << ans << endl;

    return 0;
}