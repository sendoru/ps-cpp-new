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
            int max_cnt = m.rbegin()->second.size();
            int min_cnt = m.begin()->second.size();
            auto max_chunk = get_chunk(m.rbegin()->second);
            auto min_chunk = get_chunk(m.begin()->second);

            // 양 끝에
            if (max_cnt >= n / 2 && max_chunk.size() == 1) {
                if (max_chunk[0].first == 0) {
                    cout << "Case #" << test_case + 1 << "\n";
                    cout << 1 << "\n";
                    cout << 1 << " " << (n + 2) / 2 << " " << n << "\n";
                    continue;
                }
                else if (max_chunk[0].second == n - 1) {
                    cout << "Case #" << test_case + 1 << "\n";
                    cout << 1 << "\n";
                    cout << 1 << " " << 1 << " " << (n + 1) / 2 << "\n";
                    continue;
                }
            }
            if (max_cnt >= n / 2 && max_chunk.size() == 2 && max_chunk[0].first == 0 && max_chunk[1].second == n - 1) {
                int min_idx = min_chunk[0].first;
                int l = min_idx, r = min_idx;
                for (; l > 0 && a[l - 1] != max_val; l--) {
                }
                for (; r < n - 1 && a[r + 1] != max_val; r++) {
                }
                for (; l > 0 && max_cnt > n / 2; l--, max_cnt--) {
                }
                for (; r < n - 1 && max_cnt > n / 2; r++, max_cnt--) {
                }
                cout << "Case #" << test_case + 1 << "\n";
                cout << 1 << "\n";
                cout << 1 << " " << l + 1 << " " << r + 1 << "\n";
                continue;
            }

            if (min_cnt >= n / 2 && min_chunk.size() == 1) {
                if (min_chunk[0].first == 0) {
                    cout << "Case #" << test_case + 1 << "\n";
                    cout << 1 << "\n";
                    cout << 2 << " " << (n + 2) / 2 << " " << n << "\n";
                    continue;
                }
                else if (min_chunk[0].second == n - 1) {
                    cout << "Case #" << test_case + 1 << "\n";
                    cout << 1 << "\n";
                    cout << 2 << " " << 1 << " " << (n + 1) / 2 << "\n";
                    continue;
                }
            }
            if (min_cnt >= n / 2 && min_chunk.size() == 2 && min_chunk[0].first == 0 && min_chunk[1].second == n - 1) {
                int max_idx = max_chunk[0].first;
                int l = max_idx, r = max_idx;
                for (; l > 0 && a[l - 1] != min_val; l--) {
                }
                for (; r < n - 1 && a[r + 1] != min_val; r++) {
                }
                for (; l > 0 && min_cnt > n / 2; l--, min_cnt--) {
                }
                for (; r < n - 1 && min_cnt > n / 2; r++, min_cnt--) {
                }
                cout << "Case #" << test_case + 1 << "\n";
                cout << 1 << "\n";
                cout << 2 << " " << l + 1 << " " << r + 1 << "\n";
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