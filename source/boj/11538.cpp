// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const int BIT_MAX = 18;

int bitfilp(int n, int i) {
    return n ^ (1 << i);
}

vector<int> get_possible(int n) {
    vector<int> ret;
    for (int i = 0; i < BIT_MAX; i++) {
        int cur = bitfilp(n, i);
        if (cur > n) {
            ret.push_back(cur);
        }
    }
    for (int i = 0; i < BIT_MAX; i++) {
        for (int j = i + 1; j < BIT_MAX; j++) {
            int cur = bitfilp(bitfilp(n, i), j);
            if (cur > n) {
                ret.push_back(cur);
            }
        }
    }
    sort(ret.begin(), ret.end());
    ret.erase(unique(ret.begin(), ret.end()), ret.end());
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<int> v;
    int cur;
    while (true) {
        cin >> cur;
        if (cur == -1)
            break;
        v.push_back(cur);
    }

    unordered_set<int> s(v.begin(), v.end());

    for (auto n : v) {
        vector<int> possible = get_possible(n);
        int ans = 0;
        for (auto p : possible) {
            if (s.find(p) != s.end()) {
                ans++;
            }
        }
        cout << n << ":" << ans << "\n";
    }

    return 0;
}