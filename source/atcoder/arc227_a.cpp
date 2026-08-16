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
    n *= 2;
    array<vector<int>, 3> one_pos;
    vector<string> abc(3);
    for (int i = 0; i < 3; i++) {
        cin >> abc[i];
        for (int j = 0; j < n; j++) {
            if (abc[i][j] == '1') {
                one_pos[i].push_back(j);
            }
        }
    }

    vector<int> meds(n / 2);
    ll min_dist = 0;
    for (int i = 0; i < n / 2; i++) {
        array<int, 3> cur_one_pos;
        for (int j = 0; j < 3; j++) {
            cur_one_pos[j] = one_pos[j][i];
        }
        sort(cur_one_pos.begin(), cur_one_pos.end());
        meds[i] = cur_one_pos[1];
        min_dist += cur_one_pos[2] - cur_one_pos[0];
    }

    string ans(n, '0');
    for (auto med : meds) {
        ans[med] = '1';
    }

    cout << min_dist << '\n'
         << ans;

    return 0;
}