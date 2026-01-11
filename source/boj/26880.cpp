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

    ll n;
    cin >> n;
    deque<pll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a.begin(), a.end(), greater<pll>());

    int l1 = 1, l2 = n - a[l1].first;
    for (l1 = 1; l1 < n - 1; l1++) {
        l2 = n - a[l1].first;
        if (l2 - l1 >= a[0].first && l1 >= a[l2].first) {
            cout << "YES\n";
            vector<int> ans(n);
            for (int i = 0; i < l1; i++) {
                ans[a[i].second] = 1;
            }
            for (int i = l1; i < l2; i++) {
                ans[a[i].second] = 2;
            }
            for (int i = l2; i < n; i++) {
                ans[a[i].second] = 3;
            }
            for (int i = 0; i < n; i++) {
                cout << ans[i];
            }
            return 0;
        }
    }

    sort(a.begin(), a.end());

    array<vector<pll>, 3> group;

    group[0].push_back(a.back());
    a.pop_back();

    for (int i = 0; i < group[0][0].first; i++) {
        if (a.empty()) {
            cout << "NO";
            return 0;
        }
        group[1].push_back(a.front());
        a.pop_front();
    }
    for (int i = 0; i < group[1].back().first; i++) {
        if (a.empty()) {
            cout << "NO";
            return 0;
        }
        group[2].push_back(a.front());
        a.pop_front();
    }
    while(!a.empty()) {
        group[0].push_back(a.back());
        a.pop_back();
    }
    if (group[0].size() < group[2].back().first) {
        cout << "NO";
        return 0;
    }

    cout << "YES\n";
    vector<int> ans(n);
    for(auto& [_, idx]: group[0]) {
        ans[idx] = 1;
    }
    for(auto& [_, idx]: group[1]) {
        ans[idx] = 2;
    }
    for(auto& [_, idx]: group[2]) {
        ans[idx] = 3;
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i];
    }

    cout << "NO";

    return 0;
}