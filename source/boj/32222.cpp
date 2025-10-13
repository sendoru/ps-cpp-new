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
    vector<int> s(n);
    vector<int> cnt(3);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        if (2 * s[i] < m) {
            cnt[0]++;
        } else if (s[i] < m) {
            cnt[1]++;
        } else {
            cnt[2]++;
        }
    }

    if (cnt[1] < 3) {
        if (cnt[2] == 0) {
            sort(s.begin(), s.end(), greater<int>());
            // assert(s.size() < 3);
            if (s.size() >= 3 && s[1] + s[2] >= m) {
                cout << (cnt[0] + cnt[1] + 1) / 2 << '\n';
            } else if (s.size() >= 4 && s[0] + s[3] >= m && 4 * s[3] >= m && s[1] + 2 * s[3] >= m) {
                cout << (cnt[0] + cnt[1] + 1) / 2 << '\n';
            } else {
                cout << (cnt[0] + cnt[1]) / 2 + 1 << '\n';
            }
        } else {
            cout << (cnt[0] + cnt[1] + 1) / 2 << '\n';
        }
    } else {
        cout << cnt[1] / 3 + (cnt[0] + (cnt[1] % 3) + 1) / 2 << '\n';
    }

    return 0;
}