// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll get_pal_cnt(const string &s) {
    string s_new;
    for (char c : s) {
        s_new += '#';
        s_new += c;
    }
    s_new += '#';

    int n = (int)s_new.size();
    // d1[i] := s_new[i]가 중심인 제일 긴 팰린드롬의 반지름
    vector<int> d1(n);
    int l = 0, r = 0;
    for (int i = 0; i < n; i++) {
        if (r < i) {
            d1[i] = 0;
        } else {
            d1[i] = min(d1[l + r - i], r - i);
        }

        while (i - d1[i] >= 0 && i + d1[i] < n && s_new[i - d1[i]] == s_new[i + d1[i]]) {
            d1[i]++;
        }

        if (i + d1[i] > r) {
            l = i - d1[i];
            r = i + d1[i];
        }
    }

    ll res = 0;
    for (int i = 0; i < n; i++) {
        res += d1[i] / 2;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s;
    cin >> s;
    cout << get_pal_cnt(s) << "\n";

    return 0;
}