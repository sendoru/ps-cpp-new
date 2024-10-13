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

    string s;
    cin >> s;
    vector<vector<int>> chr_idx(26);
    for (int i = 0; i < s.size(); i++) {
        chr_idx[s[i] - 'A'].push_back(i);
    }

    ll ans = 0;
    for (int i = 0; i < s.size(); i++) {
        for (int chr = 0; chr < 26; chr++) {
            ll left_cnt = lower_bound(chr_idx[chr].begin(), chr_idx[chr].end(), i) - chr_idx[chr].begin();
            ll right_cnt = chr_idx[chr].size() - left_cnt;
            if (chr == s[i] - 'A') {
                right_cnt--;
            }
            ans += left_cnt * right_cnt;
        }
    }

    cout << ans;

    return 0;
}