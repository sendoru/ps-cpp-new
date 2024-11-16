#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<pii> get_cont_1s(string s)
{
    vector<pii> ans;
    int cur = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '1') {
            cur++;
        }
        else {
            if (cur > 0) {
                ans.push_back({i - cur, i});
            }
            cur = 0;
        }
    }

    if (cur > 0) {
        ans.push_back({(int)s.length() - cur, (int)s.length()});
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    cin >> n >> k;
    k--;
    string s;
    cin >> s;

    vector<int> ord(s.length(), -1);
    int cur = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            ord[i] = cur;
            cur++;
        }
    }

    auto cont_1s = get_cont_1s(s);
    cont_1s[k] = {cont_1s[k - 1].second, cont_1s[k].second - (cont_1s[k].first - cont_1s[k - 1].second)};

    vector<int> ans(n, 0);
    for (auto [s, e] : cont_1s) {
        for (int i = s; i < e; i++) {
            ans[i] = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i];
    }

    return 0;
}

// 010011111000001
// 010011111000001
