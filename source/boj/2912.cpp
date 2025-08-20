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

    random_device rd;
    mt19937 gen(rd());

    int n, c;
    cin >> n >> c;
    vector<int> colors(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> colors[i];
    }

    vector<vector<int>> by_colors(c + 1);
    for (int i = 1; i <= n; i++) {
        by_colors[colors[i]].push_back(i);
    }

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;

        bool found = false;
        uniform_int_distribution<int> dis(l, r);
        for (int i = 0; i < 50; i++) {
            int idx = dis(gen);
            int color = colors[idx];
            auto it_l = lower_bound(by_colors[color].begin(), by_colors[color].end(), l);
            auto it_r = upper_bound(by_colors[color].begin(), by_colors[color].end(), r);
            int cnt = it_r - it_l;
            if (cnt * 2 > (r - l + 1)) {
                cout << "yes " << color << "\n";
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "no\n";
        }
    }

    return 0;
}