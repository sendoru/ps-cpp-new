// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

// mitm
optional<int> subset_sum(const vector<ll> &a, ll target) {
    int n = a.size();
    vector<pair<ll, int>> left, right;
    for (int i = 0; i < (1 << n / 2); i++) {
        ll sum = 0;
        for (int j = 0; j < n / 2; j++) {
            if (i & (1 << j)) {
                sum += a[j];
            }
        }
        left.push_back({sum, i});
    }

    for (int i = 0; i < (1 << (n - n / 2)); i++) {
        ll sum = 0;
        for (int j = 0; j < n - n / 2; j++) {
            if (i & (1 << j)) {
                sum += a[j + n / 2];
            }
        }
        right.push_back({sum, i});
    }

    sort(left.begin(), left.end());
    for (auto &[sum, mask] : right) {
        ll need = target - sum;
        auto it = lower_bound(left.begin(), left.end(), make_pair(need, 0));
        if (it != left.end() && it->first == need) {
            return (mask << (n / 2)) | it->second;
        }
    }

    return nullopt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll ans = 0;
    ll target = accumulate(a.begin(), a.end(), 0LL) / m;
    vector<ll> frac;
    for (int i = 0; i < n; i++) {
        ans += a[i] / target;
        if (a[i] % target > 0) {
            frac.push_back(a[i] % target);
        } else {
            ans--;
        }
    }

    ll frac_ans = 1e9;
    for (int _ = 0; _ < 1000; _++) {
        random_shuffle(frac.begin(), frac.end());
        auto frac_copy = frac;
        ll cur_frac_ans = 0;
        while (!frac_copy.empty()) {
            ll sum = accumulate(frac_copy.begin(), frac_copy.end(), 0LL);
            assert(sum % target == 0);
            if (sum == target) {
                break;
            }
            auto mask = subset_sum(frac_copy, target);
            if (mask.has_value()) {
                vector<ll> new_frac;
                for (int i = 0; i < frac_copy.size(); i++) {
                    if (!(mask.value() & (1 << i))) {
                        new_frac.push_back(frac_copy[i]);
                    }
                }
                frac_copy = new_frac;
            } else {
                ll sum = 0;
                int i;
                for (i = 0; i < frac_copy.size(); i++) {
                    sum += frac_copy[i];
                    if (sum >= target) {
                        sum -= target;
                        cur_frac_ans++;
                        break;
                    }
                }
                vector<ll> new_frac;
                for (int j = i + 1; j < frac_copy.size(); j++) {
                    new_frac.push_back(frac_copy[j]);
                }
                new_frac.push_back(sum);
                frac_copy = new_frac;
            }
        }
        frac_ans = min(frac_ans, cur_frac_ans);
    }

    cout << ans + frac_ans;
    return 0;
}