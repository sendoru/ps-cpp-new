// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<int> solve(int n, vector<int> &sums) {
    vector<int> ans;
    sort(sums.begin(), sums.end());
    multiset<int> st;
    for (int i = 0; i < sums.size(); i++) {
        st.insert(sums[i]);
    }
    while (ans.size() < n) {
        ans.push_back(*st.begin());
        st.erase(st.find(*st.begin()));
        multiset<int> nxt;
        while (!st.empty()) {
            int v1 = *st.rbegin();
            int v2 = v1 - ans.back();
            st.erase(st.find(v1));
            if (st.find(v2) == st.end()) {
                return {};
            }
            st.erase(st.find(v2));
            nxt.insert(v2);
        }
        st = nxt;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> sums((1 << n) - 1);
        for (int i = 0; i < sums.size(); i++) {
            cin >> sums[i];
        }
        vector<int> ans = solve(n, sums);
        if (ans.empty()) {
            cout << "NO\n";
        } else {
            for (auto &x : ans) {
                cout << x << ' ';
            }
            cout << '\n';
        }
    }

    return 0;
}