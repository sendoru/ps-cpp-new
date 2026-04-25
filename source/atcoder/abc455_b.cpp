// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<string> rotate_180(const vector<string> &grid) {
    int h = grid.size();
    int w = grid[0].size();
    vector<string> res(h);
    for (int i = 0; i < h; i++) {
        res[i] = grid[h - 1 - i];
        reverse(res[i].begin(), res[i].end());
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int h, w;
    cin >> h >> w;
    vector<string> grid(h);
    for (int i = 0; i < h; i++) {
        cin >> grid[i];
    }

    int ans = 0;

    for (int r1 = 0; r1 < h; r1++) {
        for (int r2 = r1; r2 < h; r2++) {
            for (int c1 = 0; c1 < w; c1++) {
                for (int c2 = c1; c2 < w; c2++) {
                    vector<string> sub(r2 - r1 + 1);
                    for (int i = r1; i <= r2; i++) {
                        sub[i - r1] = grid[i].substr(c1, c2 - c1 + 1);
                    }
                    if (sub == rotate_180(sub)) {
                        ans++;
                    }
                }
            }
        }
    }

    cout << ans;

    return 0;
}