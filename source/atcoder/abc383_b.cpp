// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int get_l1_dist(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

int get_cnt(vector<string> &room, int d, int r1, int c1, int r2, int c2)
{
    int ans = 0;
    int h = room.size(), w = room[0].size();
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            if (room[r][c] == '.' && (get_l1_dist(r1, c1, r, c) <= d || get_l1_dist(r2, c2, r, c) <= d)) {
                ans++;
            }
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int h, w, d;
    cin >> h >> w >> d;

    vector<string> room(h);
    for (int i = 0; i < h; i++) {
        cin >> room[i];
    }

    int ans = 0;

    for (int r1 = 0; r1 < h; r1++) {
        for (int c1 = 0; c1 < w; c1++) {
            if (room[r1][c1] == '#') {
                continue;
            }
            for (int r2 = 0; r2 < h; r2++) {
                for (int c2 = 0; c2 < w; c2++) {
                    if (room[r2][c2] == '#') {
                        continue;
                    }
                    ans = max(ans, get_cnt(room, d, r1, c1, r2, c2));
                }
            }
        }
    }

    cout << ans << '\n';

    return 0;
}