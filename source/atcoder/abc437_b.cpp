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

    int h, w, n;
    cin >> h >> w >> n;
    vector<vector<int>> a(h, vector<int>(w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> a[i][j];
        }
    }

    vector<int> cnt(h);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        for (int j = 0; j < h; j++) {
            for (int k = 0; k < w; k++) {
                if (a[j][k] == x) {
                    cnt[j]++;
                }
            }
        }
    }

    cout << *max_element(cnt.begin(), cnt.end());

    return 0;
}