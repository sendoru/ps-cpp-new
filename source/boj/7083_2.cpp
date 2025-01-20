// #include "atcoder/all"
// #pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

bool cross(pii a, pii b) {
    // assuming first < second
    return (a.first < b.first && b.first < a.second && a.second < b.second) ||
           (b.first < a.first && a.first < b.second && b.second < a.second);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<pii> v(m);
    for (int i = 0; i < m; i++) {
        cin >> v[i].first >> v[i].second;
        if (v[i].first > v[i].second) {
            swap(v[i].first, v[i].second);
        }
    }

    vector<int> side(m, -1);
    for (int i = 0; i < m; i++) {
        bool possible = true;
        int cur_side = 0;
        for (int j = 0; j < i; j++) {
            if (cur_side == side[j] && cross(v[i], v[j])) {
                if (cur_side == 1) {
                    possible = false;
                    break;
                } else {
                    cur_side = 1;
                }
            }
        }
        if (!possible) {
            cout << i << endl;
            return 0;
        }
        side[i] = cur_side;
    }
    cout << m << endl;
    return 0;
}