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
    vector<int> a(n), cnt(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }

    int less_cnt = 0;
    for (int i = 0; i < n; i++) {
        if (cnt[i] > 0 && less_cnt < i) {
            cout << "No";
            return 0;
        }
        less_cnt += cnt[i];
    }

    list<int> ans;
    auto iter_to_add = ans.begin();
    for (int x = 0; x < n; x++) {
        auto iter = iter_to_add;
        for (int i = 0; i < cnt[x]; i++) {
            if (iter == ans.end()) {
                ans.push_back(x);
            } else {
                ans.insert(next(iter), x);
            }
        }
        iter_to_add++;
    }

    cout << "Yes\n";
    for (auto x : ans) {
        cout << x << ' ';
    }

    return 0;
}