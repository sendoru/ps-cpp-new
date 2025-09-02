// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<int> get_sa(const string &s) {
    int n = s.size();
    vector<int> sa(n);
    vector<int> group(n + 1);
    vector<int> new_group(n + 1);

    for (int i = 0; i < n; i++) {
        sa[i] = i;
        group[i] = s[i];
    }

    for (int diff = 1; diff < n; diff <<= 1) {
        auto cmp = [&](int i, int j) {
            if (group[i] == group[j]) {
                return group[i + diff] < group[j + diff];
            }
            return group[i] < group[j];
        };
        sort(sa.begin(), sa.end(), cmp);

        new_group[sa[0]] = 1;
        for (int i = 1; i < n; i++) {
            new_group[sa[i]] = new_group[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        }
        group = new_group;
    }
    return sa;
}

vector<int> get_lcp_array(const string &s, vector<int> &sa) {
    int n = s.size();
    vector<int> lcp(n);
    vector<int> pos(n);
    for (int i = 0; i < n; i++) {
        pos[sa[i]] = i;
    }

    for (int i = 0, k = 0; i < n; i++) {
        if (pos[i] == n - 1) {
            continue;
        }
        for (int j = sa[pos[i] + 1]; s[i + k] == s[j + k]; k++) {
        }
        lcp[pos[i]] = k;
        if (k) {
            k--;
        }
    }
    return lcp;
}

ll solve(const string &s) {
    ll n = s.size();
    vector<int> sa = get_sa(s);
    vector<int> lcp = get_lcp_array(s, sa);

    ll ans = (n + 1) * n / 2;
    for (int i = 0; i < n - 1; i++) {
        ans -= lcp[i];
    }
    return ans;
}

ll solve_naive(const string &s) {
    ll n = s.size();
    set<string> st;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            st.insert(s.substr(i, j - i));
        }
    }
    return st.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef DEBUG
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 100; i++) {
        int n = rand() % 100 + 1;
        string s;
        for (int j = 0; j < n; j++) {
            s += 'a' + rand() % 26;
        }
        ll ans1 = solve(s);
        ll ans2 = solve_naive(s);
        if (ans1 != ans2) {
            cout << "Wrong!" << "\n";
            cout << s << "\n";
            cout << ans1 << " " << ans2 << "\n";
            return 0;
        }
    }
#endif

    string s;
    cin >> s;
    cout << solve(s) << "\n";

    return 0;
}