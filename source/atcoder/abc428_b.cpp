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

    int n, k;
    cin >> n >> k;

    string str;
    cin >> str;
    map<string, int> sub_cnt;

    for (int s = 0; s + k <= str.size(); s++) {
        sub_cnt[str.substr(s, k)]++;
    }

    ll max_cnt = 0;
    for (auto [sub, cnt] : sub_cnt) {
        max_cnt = max(max_cnt, (ll)cnt);
    }

    vector<string> ans;
    for (auto [sub, cnt] : sub_cnt) {
        if (cnt == max_cnt) {
            ans.push_back(sub);
        }
    }

    sort(ans.begin(), ans.end());

    cout << max_cnt << "\n";
    for (auto s : ans) {
        cout << s << " ";
    }

    return 0;
}