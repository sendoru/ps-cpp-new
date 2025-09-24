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
    vector<pii> ab(n);
    for (int i = 0; i < n; i++) {
        cin >> ab[i].first >> ab[i].second;
    }

    sort(ab.begin(), ab.end());
    vector<int> pre(n, -1);
    vector<int> st;
    st.push_back(0);
    for (int i = 1; i < n; i++) {
        auto iter = lower_bound(st.begin(), st.end(), i, [&](int x, int y) {
            return ab[x].second < ab[y].second;
        });
        if (iter == st.end()) {
            pre[i] = st.back();
            st.push_back(i);
        } else {
            if (iter != st.begin()) {
                pre[i] = *(iter - 1);
            }
            *iter = i;
        }
    }

    vector<bool> check(n, true);
    int cur = st.back();
    while (cur != -1) {
        check[cur] = false;
        cur = pre[cur];
    }
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (check[i]) {
            ans.push_back(ab[i].first);
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (int x : ans) {
        cout << x << '\n';
    }

    return 0;
}