// #include "atcoder/all"
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

map<string, ll> zero;
ll one[6][12'123'123];
ll two[36][567'567];

ll encode(string s) {
    ll hash = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != '?') {
            hash *= 26;
            hash += s[i] - 'a';
        }
    }
    return hash;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> ss(n);
    for (int i = 0; i < n; i++) {
        cin >> ss[i];
    }

    ll ans = 0;

    for (auto s : ss) {
        // find matchings
        vector<ll> matchings(3, 0);
        // dist == 0
        matchings[0] = zero[s];

        // dist == 1
        for (int i = 0; i < m; i++) {
            string tmp = s;
            tmp[i] = '?';
            matchings[1] += one[i][encode(tmp)];
        }

        // dist == 2
        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                string tmp = s;
                tmp[i] = '?';
                tmp[j] = '?';
                matchings[2] += two[i * m + j][encode(tmp)];
            }
        }
        matchings[1] -= matchings[0] * m;
        matchings[2] -= matchings[1] * (m - 1);
        matchings[2] -= matchings[0] * (m * (m - 1) / 2);
        ans += matchings[0] + matchings[1] + matchings[2];

        // add to dict
        zero[s]++;
        for (int i = 0; i < m; i++) {
            string tmp = s;
            tmp[i] = '?';
            one[i][encode(tmp)]++;
        }
        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                string tmp = s;
                tmp[i] = '?';
                tmp[j] = '?';
                two[i * m + j][encode(tmp)]++;
            }
        }
    }

    cout << ans;

    return 0;
}