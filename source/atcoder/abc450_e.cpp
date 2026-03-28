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

    string x, y;
    cin >> x >> y;
    vector<ll> fib;
    fib.push_back(x.size());
    fib.push_back(y.size());
    while (fib.back() <= 1e18) {
        fib.push_back(fib[fib.size() - 1] + fib[fib.size() - 2]);
    }

    vector<vector<ll>> cnt(26, vector<ll>(fib.size()));
    for (int i = 0; i < x.size(); i++) {
        cnt[x[i] - 'a'][0]++;
    }
    for (int i = 0; i < y.size(); i++) {
        cnt[y[i] - 'a'][1]++;
    }
    for (int i = 2; i < fib.size(); i++) {
        for (int j = 0; j < 26; j++) {
            cnt[j][i] = cnt[j][i - 1] + cnt[j][i - 2];
        }
    }

    vector<vector<ll>> cnt_x(26, vector<ll>(x.size())), cnt_y(26, vector<ll>(y.size()));
    cnt_x[x[0] - 'a'][0]++;
    for (int i = 1; i < x.size(); i++) {
        for (int j = 0; j < 26; j++) {
            cnt_x[j][i] = cnt_x[j][i - 1];
        }
        cnt_x[x[i] - 'a'][i]++;
    }

    cnt_y[y[0] - 'a'][0]++;
    for (int i = 1; i < y.size(); i++) {
        for (int j = 0; j < 26; j++) {
            cnt_y[j][i] = cnt_y[j][i - 1];
        }
        cnt_y[y[i] - 'a'][i]++;
    }

    function<ll(ll, char)> get_cnt = [&](ll len, char c) -> ll {
        if (len <= 0) {
            return 0;
        } else if (len <= y.size()) {
            return cnt_y[c - 'a'][len - 1];
        } else if (len <= y.size() + x.size()) {
            return cnt_y[c - 'a'].back() + cnt_x[c - 'a'][len - y.size() - 1];
        }
        int idx = lower_bound(fib.begin(), fib.end(), len) - fib.begin();
        idx--;
        return cnt[c - 'a'][idx] + get_cnt(len - fib[idx], c);
    };

    int q;
    cin >> q;
    while (q--) {
        ll l, r;
        cin >> l >> r;
        char c;
        cin >> c;
        cout << get_cnt(r, c) - get_cnt(l - 1, c) << '\n';
    }

    return 0;
}