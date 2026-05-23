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

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i] -= i;
            a[i] += n; // to avoid negative values
        }

        // {val, cnt}
        // make this non-decreasing
        vector<array<ll, 2>> monostack;
        for (int i = 0; i < n; i++) {
            monostack.push_back({a[i], 1});
            while (true) {
                if (monostack.size() < 2) {
                    break;
                }
                // ceil(avg[prev])
                ll prev_max = (monostack[monostack.size() - 2][0] + monostack[monostack.size() - 2][1] - 1) / monostack[monostack.size() - 2][1];
                // floor(avg[curr])
                ll curr_min = monostack.back()[0] / monostack.back()[1];
                if (prev_max <= curr_min) {
                    break;
                }

                // merge
                auto [prev_sum, prev_cnt] = monostack[monostack.size() - 2];
                auto [curr_sum, curr_cnt] = monostack.back();
                monostack.pop_back();
                monostack.back()[0] = prev_sum + curr_sum;
                monostack.back()[1] = prev_cnt + curr_cnt;
            }
        }

        vector<ll> recon_a;
        for (auto &[sum, cnt] : monostack) {
            // floor(avg)
            ll val = sum / cnt;
            ll mod = sum % cnt;
            if (mod == 0) {
                for (int i = 0; i < cnt; i++) {
                    recon_a.push_back(val);
                }
            } else {
                for (int i = 0; i < cnt - mod; i++) {
                    recon_a.push_back(val);
                }
                for (int i = 0; i < mod; i++) {
                    recon_a.push_back(val + 1);
                }
            }
        }

        vector<ll> prefix_sum_orig(n + 1), prefix_sum_recon(n + 1);
        for (int i = 0; i < n; i++) {
            prefix_sum_orig[i + 1] = prefix_sum_orig[i] + a[i];
            prefix_sum_recon[i + 1] = prefix_sum_recon[i] + recon_a[i];
        }
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            ans += abs(prefix_sum_orig[i + 1] - prefix_sum_recon[i + 1]);
        }
        cout << ans << "\n";
    }

    return 0;
}