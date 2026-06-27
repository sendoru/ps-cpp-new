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
    vector<array<ll, 3>> adb(n);
    for (int i = 0; i < n; i++) {
        cin >> adb[i][0] >> adb[i][1] >> adb[i][2];
    }

    sort(adb.begin(), adb.end(), [](const array<ll, 3> &a, const array<ll, 3> &b) {
        return a[1] < b[1];
    });

    map<ll, ll> color_cnt;
    for (int i = 0; i < n; i++) {
        color_cnt[adb[i][0]]++;
    }

    auto it = adb.begin();
    for (int i = 1; i <= m; i++) {
        while (it != adb.end() && (*it)[1] <= i) {
            color_cnt[(*it)[0]]--;
            if (color_cnt[(*it)[0]] == 0) {
                color_cnt.erase((*it)[0]);
            }
            color_cnt[(*it)[2]]++;
            it++;
        }
        cout << color_cnt.size() << '\n';
    }

    return 0;
}