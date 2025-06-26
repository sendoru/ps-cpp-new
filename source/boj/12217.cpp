// #include "atcoder/all"
#pragma GCC optimize("O3,Ofast,unroll-loops")
#include <bits/stdc++.h>
// #define DEBUG

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

template <typename T>
int diff_cnt(const vector<T> &a, const vector<T> &b) {
    int cnt = 0;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            cnt++;
        }
    }
    return cnt;
}

ll solve(vector<int> a) {
    int n = (int)(round(log2(a.size())));
    vector<int> sorted(a.size());
    iota(sorted.begin(), sorted.end(), 0);
    vector<ll> ans(n + 1, 0);

    function<void(vector<int>, int, int)> dfs = [&](vector<int> cur_a, int log_block_sz, int swap_cnt) {
        if (log_block_sz == n) {
            if (cur_a == sorted) {
                ans[swap_cnt]++;
            }
            return;
        }

        int block_sz = 1 << log_block_sz, block_cnt = cur_a.size() / block_sz;

        // check if each blocks are sorted
        for (int start_idx = 0; start_idx < a.size(); start_idx += block_sz) {
            int start = cur_a[start_idx];
            if (start & ((1 << log_block_sz) - 1)) {
                return;
            }
            for (int j = start_idx + 1; j < start_idx + block_sz; j++) {
                if (cur_a[j] != cur_a[j - 1] + 1) {
                    return;
                }
            }
        }

        dfs(cur_a, log_block_sz + 1, swap_cnt);

        // check further
        int next_error_cnt = 0;
        for (int start_idx = 0; start_idx < a.size(); start_idx += 2 * block_sz) {
            int start = cur_a[start_idx];
            if (start & ((2 << log_block_sz) - 1)) {
                next_error_cnt++;
                continue;
            }
            for (int j = start_idx + 1; j < start_idx + 2 * block_sz; j++) {
                if (cur_a[j] != cur_a[j - 1] + 1) {
                    next_error_cnt++;
                    break;
                }
            }
        }

        if (next_error_cnt > 2) {
            return;
        }

        for (int i = 0; i < a.size(); i += block_sz) {
            int i_next_start = i / (2 * block_sz) * (2 * block_sz);
            bool is_swap_needed = false;
            for (int j = i_next_start + 1; j < i_next_start + 2 * block_sz; j++) {
                if (cur_a[j] != cur_a[j - 1] + 1) {
                    is_swap_needed = true;
                    break;
                }
            }

            if (!is_swap_needed) {
                continue;
            }

            for (int j = i + block_sz; j < a.size(); j += block_sz) {
                int j_next_start = j / (2 * block_sz) * (2 * block_sz);
                is_swap_needed = false;
                for (int k = j_next_start + 1; k < j_next_start + 2 * block_sz; k++) {
                    if (cur_a[k] != cur_a[k - 1] + 1) {
                        is_swap_needed = true;
                        break;
                    }
                }
                if (!is_swap_needed) {
                    continue;
                }

                vector<int> next_a = cur_a;
                for (int k = 0; k < block_sz; ++k) {
                    swap(next_a[i + k], next_a[j + k]);
                }

                int start = next_a[i_next_start];
                if (start & ((2 << log_block_sz) - 1)) {
                    continue;
                }
                for (int k = i_next_start + 1; k < i_next_start + 2 * block_sz; k++) {
                    if (next_a[k] != next_a[k - 1] + 1) {
                        continue;
                    }
                }

                start = next_a[j_next_start];
                if (start & ((2 << log_block_sz) - 1)) {
                    continue;
                }
                for (int k = j_next_start + 1; k < j_next_start + 2 * block_sz; k++) {
                    if (next_a[k] != next_a[k - 1] + 1) {
                        continue;
                    }
                }
                dfs(next_a, log_block_sz + 1, swap_cnt + 1);
            }
        }
    };

    dfs(a, 0, 0);
    ll res = 0;
    ll fact = 1;
    for (int i = 0; i <= n; i++) {
        if (i != 0) {
            fact *= i;
        }
        res += ans[i] * fact;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef DEBUG
    int n = 12;
    vector<int> a(1 << n);
    iota(a.begin(), a.end(), 0);
    random_device rd;
    mt19937 g(rd());
    shuffle(a.begin(), a.end(), g);

    ll time_start = chrono::steady_clock::now().time_since_epoch().count();
    ll result = solve(a);
    ll time_end = chrono::steady_clock::now().time_since_epoch().count();
    cout << "Time taken: " << (time_end - time_start) / 1000000 << " ms\n";
    cout << "Result: " << result << "\n";
    cout << flush;
#endif

    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int n;
        cin >> n;
        vector<int> a(1 << n);
        for (int i = 0; i < (1 << n); i++) {
            cin >> a[i];
            a[i]--;
        }
        ll result = solve(a);
        cout << "Case #" << t << ": " << result << "\n";
    }

    return 0;
}