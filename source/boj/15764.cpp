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

    int n, m, k;
    cin >> n >> m >> k;
    deque<int> a(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
        a[i]--;
    }

    vector<int> v(n, -1);
    for (int i = 0; i < k; i++) {
        int no, pos;
        cin >> no >> pos;
        v[pos - 1] = no - 1;
    }

    auto bound_rev = v.rbegin();
    while (!a.empty()) {
        int no = a.back();
        if (no == 0) {
            break;
        }
        a.pop_back();
        auto cur_iter = find(bound_rev, v.rend(), no);
        if (cur_iter == v.rend()) {
            cur_iter = find(bound_rev, v.rend(), -1);
            *cur_iter = no;
        } else {
            bound_rev = cur_iter + 1;
        }
    }

    auto bound = v.begin();
    while (!a.empty()) {
        int no = a.front();
        a.pop_front();
        auto cur_iter = find(bound, v.end(), no);
        if (cur_iter == v.end()) {
            cur_iter = find(bound, v.end(), -1);
            *cur_iter = no;
        } else {
            bound = cur_iter + 1;
        }
    }

    auto iter = find(v.begin(), v.end(), 0);
    if (iter == v.end()) {
        cout << find(v.begin(), v.end(), -1) - v.begin() + 1;
    } else {
        cout << iter - v.begin() + 1;
    }
    return 0;
}