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
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    if (n == 1) {
        cout << a[1] << ' ';
        for (int i = 0; i < a[1]; i++) {
            cout << 2 << ' ';
        }
        return 0;
    }

    int all_cnt = a[1];
    map<int, int> cnt;
    for (int cur = 2; all_cnt > 0; cur++) {
        int cur_cnt = a[cur];
        for (int j = 2; j < cur; j++) {
            cur_cnt -= cnt[j] * (cur % j);
        }
        cur_cnt = cur_cnt / cur - all_cnt;
        cur_cnt *= -1;
        cnt[cur] = cur_cnt;
        all_cnt -= cur_cnt;
    }

    vector<int> ans;
    for (auto [num, cnt] : cnt) {
        for (int i = 0; i < cnt; i++) {
            ans.push_back(num);
        }
    }

    cout << ans.size() << ' ';
    for (auto num : ans) {
        cout << num << ' ';
    }

    return 0;
}