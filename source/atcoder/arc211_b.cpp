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

    int x, y, z;
    cin >> x >> y >> z;
    // check if zero-fill works
    int s1_len = max(x, y), s2_len = max(x, z), s3_len = max(y, z);
    if (min(s1_len, s2_len) == x && min(s1_len, s3_len) == y && min(s2_len, s3_len) == z) {
        cout << s1_len << ' ';
        for (int i = 0; i < s1_len; i++) {
            cout << "0 ";
        }
        cout << '\n';

        cout << s2_len << ' ';
        for (int i = 0; i < s2_len; i++) {
            cout << "0 ";
        }
        cout << '\n';

        cout << s3_len << ' ';
        for (int i = 0; i < s3_len; i++) {
            cout << "0 ";
        }
        cout << '\n';

        return 0;
    }

    vector<array<int, 3>> xyz_sorted = {{x, 0, 1}, {y, 0, 2}, {z, 1, 2}};
    sort(xyz_sorted.begin(), xyz_sorted.end(), greater<array<int, 3>>());
    vector<string> ans_pre(3);
    ans_pre[0] = string(xyz_sorted[0][0], '0') + string(xyz_sorted[0][0], '1');
    ans_pre[1] = string(2 * xyz_sorted[0][0], '0');
    ans_pre[2] = string(xyz_sorted[2][0], '0') + string(xyz_sorted[1][0] - xyz_sorted[2][0], '1');

    vector<string> ans(3);
    for (int i = 0; i < 3; i++) {
        map<int, int> cnt;
        if (i == 0) {
            cnt[xyz_sorted[0][1]]++;
            cnt[xyz_sorted[0][2]]++;
            cnt[xyz_sorted[1][1]]++;
            cnt[xyz_sorted[1][2]]++;
        }
        else if (i == 1) {
            cnt[xyz_sorted[0][1]]++;
            cnt[xyz_sorted[0][2]]++;
            cnt[xyz_sorted[2][1]]++;
            cnt[xyz_sorted[2][2]]++;
        }
        else {
            cnt[xyz_sorted[1][1]]++;
            cnt[xyz_sorted[1][2]]++;
            cnt[xyz_sorted[2][1]]++;
            cnt[xyz_sorted[2][2]]++;
        }
        int idx;
        for (auto [k, v] : cnt) {
            if (v == 2) {
                idx = k;
                break;
            }
        }
        ans[idx] = ans_pre[i];
    }

    for (int i = 0; i < 3; i++) {
        cout << ans[i].size() << ' ';
        for (char c : ans[i]) {
            cout << c << ' ';
        }
        cout << '\n';
    }


    return 0;
}