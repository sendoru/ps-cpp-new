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

    int n, m;
    cin >> n >> m;

    string s;
    cin >> s;
    string t;
    cin >> t;
    int q;
    cin >> q;

    for (int i = 0; i < q; i++) {
        string w;
        cin >> w;
        int s_cnt = 0, t_cnt = 0;
        for (char c : w) {
            if (s.find(c) != string::npos) {
                s_cnt++;
            }
            if (t.find(c) != string::npos) {
                t_cnt++;
            }
        }
        if (s_cnt == w.length() && t_cnt != w.length()) {
            cout << "Takahashi\n";
        } else if (s_cnt != w.length() && t_cnt == w.length()) {
            cout << "Aoki\n";
        } else {
            cout << "Unknown\n";
        }
    }

    return 0;
}