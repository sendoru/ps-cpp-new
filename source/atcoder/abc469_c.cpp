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

    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> pf_sum(n + 1);
    for (int i = 1; i <= n; i++) {
        pf_sum[i] = pf_sum[i - 1] + (s[i - 1] == 'o');
    }

    int cur_o = 0, cur_max = 0, cur_x = 0;
    for (int i = 0; i < n; i++) {
        cur_o += (s[i] == 'o');
        cur_max = max(cur_max, i);
        cur_x -= (s[i] == 'x');
        while (cur_max < n && cur_x < cur_o) {
            cur_x += (s[cur_max] == 'x');
            cur_max++;
        }
        cout << cur_max << '\n';
    }
    return 0;
}