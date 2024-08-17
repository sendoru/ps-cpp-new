#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const ll MOD1 = 1e9 + 7;
const ll MOD9 = 998244353;

vector<pll> get_chunk(vector<ll> &v)
{
    if (v.size() == 0) {
        return {};
    }
    vector<pll> ret;
    ll cur = v[0];
    for (int i = 1; i < v.size(); i++) {
        if (v[i] != v[i - 1] + 1) {
            ret.push_back({cur, v[i - 1]});
            cur = v[i];
        }
    }
    ret.push_back({cur, v.back()});

    return ret;
}

ll get_partial_sum(vector<ll> &prefix_sum, int l, int r)
{
    if (r < 0 || l < 0 || l > r) {
        return 0;
    }
    if (l == 0) {
        return prefix_sum[r];
    }
    return prefix_sum[r] - prefix_sum[l - 1];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T, test_case;
    /*
       The freopen function below opens input.txt file in read only mode, and
       afterward, the program will read from input.txt file instead of
       standard(keyboard) input. To test your program, you may save input data
       in input.txt file, and use freopen function to read from the file when
       using cin function. You may remove the comment symbols(//) in the below
       statement and use it. Use #include<cstdio> or #include <stdio.h> to use
       the function in your program. But before submission, you must remove the
       freopen function or rewrite comment symbols(//).
     */

    // freopen("../tc.txt", "r", stdin);

    cin >> T;
    for (test_case = 0; test_case < T; test_case++) {
        cout.flush();
        ll n;
        cin >> n;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        // check if unique values of a is only 2 or less
        set<ll> s(a.begin(), a.end());
        if (s.size() == 1) {
            cout << "Case #" << test_case + 1 << "\n";
            cout << 0 << "\n";
            continue;
        }
        else if (s.size() == 2) {
            map<ll, ll> m;
            for (ll x : a) {
                m[x]++;
            }
            // check if the number of each value is the same(even) or differ by 1(odd)
            int diff = m.begin()->second - m.rbegin()->second;
            if (abs(diff) <= 1) {
                cout << "Case #" << test_case + 1 << "\n";
                cout << 0 << "\n";
            }
            else {
                cout << "Case #" << test_case + 1 << "\n";
                cout << 1 << "\n";
                int to_be = m.begin()->second < m.rbegin()->second ? m.begin()->first : m.rbegin()->first;
                int l = -1, r = -1;
                for (int i = 0; i < n; i++) {
                    if (a[i] == to_be) {
                        l = r = i;
                        break;
                    }
                }
                int cur_cnt = m[to_be];
                for (; r < n - 1 && cur_cnt < n / 2; r++) {
                    if (a[r + 1] != to_be) {
                        // r++;
                        cur_cnt++;
                    }
                }
                for (; l > 0 && cur_cnt < n / 2; l--) {
                    if (a[l - 1] != to_be) {
                        // l--;
                        cur_cnt++;
                    }
                }

                if (to_be == m.begin()->first) {
                    cout << 1 << " " << l + 1 << " " << r + 1 << "\n";
                }
                else {
                    cout << 2 << " " << l + 1 << " " << r + 1 << "\n";
                }
            }
            continue;
        }

        else {
            map<ll, vector<ll>> m;
            for (int i = 0; i < n; i++) {
                m[a[i]].push_back(i);
            }
            int max_val = m.rbegin()->first;
            int min_val = m.begin()->first;
            vector<ll> min_elem_cnt_prefix(n);
            vector<ll> max_elem_cnt_prefix(n);
            min_elem_cnt_prefix[0] = a[0] == min_val;
            max_elem_cnt_prefix[0] = a[0] == max_val;
            for (int i = 1; i < n; i++) {
                min_elem_cnt_prefix[i] = min_elem_cnt_prefix[i - 1] + (a[i] == min_val);
                max_elem_cnt_prefix[i] = max_elem_cnt_prefix[i - 1] + (a[i] == max_val);
            }
            bool done = false;
            for (int i = 0; i < n && !done; i++) {
                ll target = ceil(n / 2.) - get_partial_sum(min_elem_cnt_prefix, 0, i - 1);
                // find maximum m such that changing a[i], a[i+1], ..., a[m] to min_val makes the number of min_val in the array to be ceil(n/2)
                ll l = i, r = n - 1;
                ll j = -1;
                while (l <= r) {
                    ll mid = (l + r) / 2;
                    if ((mid - i + 1) - get_partial_sum(min_elem_cnt_prefix, i, mid) + get_partial_sum(min_elem_cnt_prefix, i, n - 1) <= target) {
                        l = mid + 1;
                    }
                    else {
                        r = mid - 1;
                    }
                    if ((mid - i + 1) - get_partial_sum(min_elem_cnt_prefix, i, mid) + get_partial_sum(min_elem_cnt_prefix, i, n - 1) == target) {
                        j = max(j, (ll)mid);
                    }
                }
                if (j == -1) {
                    continue;
                }
                if (get_partial_sum(min_elem_cnt_prefix, i, j) == 0) {
                    continue;
                }
                if (get_partial_sum(max_elem_cnt_prefix, 0, i - 1) +
                        get_partial_sum(max_elem_cnt_prefix, j + 1, n - 1) <
                    n / 2) {
                    continue;
                }
                if (get_partial_sum(max_elem_cnt_prefix, 0, i - 1) +
                        get_partial_sum(max_elem_cnt_prefix, j + 1, n - 1) + get_partial_sum(min_elem_cnt_prefix, 0, i - 1) +
                        get_partial_sum(min_elem_cnt_prefix, j + 1, n - 1) !=
                    (n - (j - i + 1))) {
                    continue;
                }
                done = true;
                cout << "Case #" << test_case + 1 << "\n";
                cout << 1 << "\n";
                cout << 1 << " " << i + 1 << " " << j + 1 << "\n";
            }
            if (done) {
                continue;
            }
            for (int i = 0; i < n && !done; i++) {
                ll target = ceil(n / 2.) - get_partial_sum(max_elem_cnt_prefix, 0, i - 1);
                // find maximum m such that changing a[i], a[i+1], ..., a[m] to max_val makes the number of max_val in the array to be ceil(n/2)
                ll l = i, r = n - 1;
                ll j = -1;
                while (l <= r) {
                    ll mid = (l + r) / 2;
                    if ((mid - i + 1) - get_partial_sum(max_elem_cnt_prefix, i, mid) + get_partial_sum(max_elem_cnt_prefix, i, n - 1) <= target) {
                        l = mid + 1;
                    }
                    else {
                        r = mid - 1;
                    }
                    if ((mid - i + 1) - get_partial_sum(max_elem_cnt_prefix, i, mid) + get_partial_sum(max_elem_cnt_prefix, i, n - 1) == target) {
                        j = max(j, (ll)mid);
                    }
                }
                if (j == -1) {
                    continue;
                }
                if (get_partial_sum(max_elem_cnt_prefix, i, j) == 0) {
                    continue;
                }
                if (get_partial_sum(min_elem_cnt_prefix, 0, i - 1) +
                        get_partial_sum(min_elem_cnt_prefix, j + 1, n - 1) <
                    n / 2) {
                    continue;
                }
                if (get_partial_sum(max_elem_cnt_prefix, 0, i - 1) +
                        get_partial_sum(max_elem_cnt_prefix, j + 1, n - 1) + get_partial_sum(min_elem_cnt_prefix, 0, i - 1) +
                        get_partial_sum(min_elem_cnt_prefix, j + 1, n - 1) !=
                    (n - (j - i + 1))) {
                    continue;
                }
                done = true;
                cout << "Case #" << test_case + 1 << "\n";
                cout << 1 << "\n";
                cout << 2 << " " << i + 1 << " " << j + 1 << "\n";
            }

            if (done) {
                continue;
            }
        }

        int min_idx = min_element(a.begin(), a.end()) - a.begin();
        int max_idx = max_element(a.begin(), a.end()) - a.begin();
        double middle = (n - 1) / 2.;
        if (min_idx < middle && max_idx > middle) {
            cout << "Case #" << test_case + 1 << "\n";
            cout << 2 << "\n";
            cout << 1 << " " << 1 << " " << (int)floor(middle) + 1 << "\n";
            cout << 2 << " " << (int)floor(middle) + 2 << " " << n << "\n";
        }
        else if (min_idx > middle && max_idx < middle) {
            cout << "Case #" << test_case + 1 << "\n";
            cout << 2 << "\n";
            cout << 2 << " " << 1 << " " << (int)floor(middle) + 1 << "\n";
            cout << 1 << " " << (int)floor(middle) + 2 << " " << n << "\n";
        }

        else if (min_idx < max_idx && max_idx <= middle) {
            cout << "Case #" << test_case + 1 << "\n";
            cout << 2 << "\n";
            cout << 2 << " " << max_idx + 1 << " " << n << "\n";
            cout << 1 << " " << 1 << " " << floor(middle) + 1 << "\n";
        }
        else if (max_idx < min_idx && min_idx <= middle) {
            cout << "Case #" << test_case + 1 << "\n";
            cout << 2 << "\n";
            cout << 1 << " " << min_idx + 1 << " " << n << "\n";
            cout << 2 << " " << 1 << " " << floor(middle) + 1 << "\n";
        }

        else if (min_idx < max_idx && min_idx >= middle) {
            cout << "Case #" << test_case + 1 << "\n";
            cout << 2 << "\n";
            cout << 1 << " " << 1 << " " << min_idx + 1 << "\n";
            cout << 2 << " " << floor(middle) + 2 << " " << n << "\n";
        }

        else if (max_idx < min_idx && max_idx >= middle) {
            cout << "Case #" << test_case + 1 << "\n";
            cout << 2 << "\n";
            cout << 2 << " " << 1 << " " << max_idx + 1 << "\n";
            cout << 1 << " " << floor(middle) + 2 << " " << n << "\n";
        }
    }
    cout.flush();
    return 0;
}