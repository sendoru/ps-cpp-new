#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

pll extended_euclidean(ll a, ll b)
{
    if (b == 0)
        return {1, 0};
    pll t = extended_euclidean(b, a % b);
    return {t.second, t.first - t.second * (a / b)};
}

// find primes leq n
vector<ll> get_primes(ll n)
{
    vector<ll> ret;
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i <= n; i++) {
        if (is_prime[i]) {
            ret.push_back(i);
            for (ll j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return ret;
}

// find all divisors of n
// O(sqrt(n))
vector<ll> get_divisors(ll n)
{
    vector<ll> ret;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            ret.push_back(i);
            if (i * i != n) {
                ret.push_back(n / i);
            }
        }
    }
    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        // 2ni = (i+j)(i+j+1) where 0 <= i + j < n and 0 <= i < n
        // let w = i+j
        // as w and (w+1) is mutual prime, it can solved by
        // finding mutual prime a, b s.t.
        // 1) a * b = 2n
        // 2) w % a == 0
        // 3) (w + 1) % b == 0
        // from 2), 3), w = a * x, w + 1 = b * y
        // then by-ax = 1

        vector<ll> divisors = get_divisors(2 * n);
        vector<pll> ans;
        for (ll a : divisors) {
            ll b = 2 * n / a;
            if (__gcd(a, b) != 1) {
                continue;
            }
            pll st = extended_euclidean(b, a);
            ll s = st.first, t = st.second;
            ll lower = ceil(((ld)a * t + 1) / (2 * n));
            ll upper = floor(((ld)a * t + n - 2) / (2 * n));

            // ax = w, by = w + 1
            // y = az + s, x = bz - t
            // lower <= z <= upper
            for (ll z = lower; z <= upper; z++) {
                ll x = b * z - t;
                ll y = a * z + s;
                ll w = a * x;
                if (w >= 1 && w < n - 1) {
                    // w = i + j
                    // w(w+1) = 2nr
                    // r = w(w+1) / 2n
                    ll r = w * (w + 1) / (2 * n);
                    ll c = w - r;
                    ans.push_back({r, c});
                }
            }
        }
        ans.push_back({0, 0});
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());
        // dot-symmetry
        ll sz = ans.size();
        for (ll i = 0; i < sz; i++) {
            ans.push_back({n - 1 - ans[i].first, n - 1 - ans[i].second});
        }
        // center position
        if (n % 2) {
            ans.push_back({n / 2, n / 2});
        }
        vector<ll> ans_by_val;
        for (auto &p : ans) {
            ans_by_val.push_back(n * p.first + p.second + 1);
        }
        // cout << ans_by_val.size() << ' ';
        sort(ans_by_val.begin(), ans_by_val.end());
        ans_by_val.erase(unique(ans_by_val.begin(), ans_by_val.end()),
                         ans_by_val.end());
        for (ll val : ans_by_val) {
            cout << val << ' ';
        }
        cout << '\n';
    }

    return 0;
}