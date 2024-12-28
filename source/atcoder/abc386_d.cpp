// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<pll> black, white;
    for (ll i = 0; i < m; i++) {
        ll x, y;
        char color;
        cin >> x >> y >> color;
        if (color == 'B') {
            black.push_back({x, y});
        }
        else {
            white.push_back({x, y});
        }
    }

    sort(black.begin(), black.end());
    sort(white.begin(), white.end());

    map<ll, ll> black_map;
    for (int i = 0; i < black.size(); i++) {
        black_map[black[i].first] = black[i].second;
    }

    for (auto iter = black_map.rbegin(); iter != black_map.rend(); iter++) {
        if (iter == black_map.rbegin()) {
            continue;
        }
        auto [x, y] = *iter;
        black_map[x] = max(y, (*prev(iter)).second);
    }

    for (int i = 0; i < white.size(); i++) {
        auto [x, y] = white[i];
        auto black_iter = black_map.lower_bound(x);
        if (black_iter == black_map.end()) {
            continue;
        }
        if (black_iter->second >= y) {
            cout << "No" << endl;
            return 0;
        }
    }

    cout << "Yes" << endl;

    return 0;
}