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

    string s, t;
    cin >> s >> t;
    sort(s.begin(), s.end());
    sort(t.begin(), t.end(), greater<>());
    int n = s.size();
    s.resize(n / 2 + n % 2);
    t.resize(n / 2);
    vector<int> s_cnt(26, 0), t_cnt(26, 0);
    for (char c : s) {
        s_cnt[c - 'a']++;
    }
    for (char c : t) {
        t_cnt[c - 'a']++;
    }

    vector<char> result(n);

    int s_i = 0, t_i = 'z' - 'a', result_i = 0, result_j = n - 1;
    while (s_cnt[s_i] == 0) {
        s_i++;
    }
    while (t_cnt[t_i] == 0) {
        t_i--;
    }
    int i;
    for (i = 0; i < n; i++) {
        if (i % 2 == 0) {
            if (s_i >= t_i) {
                // result[result_j--] = s_i + 'a';
                break;
            } else {
                result[result_i++] = s_i + 'a';
            }
            s_cnt[s_i]--;
            while (s_i < 26 && s_cnt[s_i] == 0) {
                s_i++;
            }
        } else {
            if (t_i <= s_i) {
                // result[result_j--] = t_i + 'a';
                break;
            } else {
                result[result_i++] = t_i + 'a';
            }
            t_cnt[t_i]--;
            while (t_i >= 0 && t_cnt[t_i] == 0) {
                t_i--;
            }
        }
    }

    s_i = 'z' - 'a', t_i = 0, result_i = n - 1;
    while (s_i >= 0 && s_cnt[s_i] == 0) {
        s_i--;
    }
    while (t_i < 26 && t_cnt[t_i] == 0) {
        t_i++;
    }

    for (; i < n; i++) {
        if (i % 2 == 0) {
            result[result_i--] = s_i + 'a';
            s_cnt[s_i]--;
            while (s_i >= 0 && s_cnt[s_i] == 0) {
                s_i--;
            }
        } else {
            result[result_i--] = t_i + 'a';
            t_cnt[t_i]--;
            while (t_i < 26 && t_cnt[t_i] == 0) {
                t_i++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << result[i];
    }

    return 0;
}