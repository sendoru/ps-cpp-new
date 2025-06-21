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

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    set<pii> intervals;
    while (q--) {
        int idx;
        cin >> idx;
        idx--;
        // w -> b
        if (a[idx] == 0) {
            a[idx] = 1;
            auto it = intervals.upper_bound({idx, idx});
            bool left_merge = (it != intervals.begin() && prev(it)->second == idx - 1);
            bool right_merge = (it != intervals.end() && it->first == idx + 1);
            if (left_merge && right_merge) {
                int left = prev(it)->first;
                int right = it->second;
                intervals.erase(prev(it));
                intervals.erase(it);
                intervals.insert({left, right});
            } else if (left_merge) {
                int left = prev(it)->first;
                intervals.erase(prev(it));
                intervals.insert({left, idx});
            } else if (right_merge) {
                int right = it->second;
                intervals.erase(it);
                intervals.insert({idx, right});
            } else {
                intervals.insert({idx, idx});
            }
        }
        // b -> w
        else {
            a[idx] = 0;
            auto it = intervals.lower_bound({idx, idx});
            if (it != intervals.end() && *it == make_pair(idx, idx)) {
                intervals.erase(it);
            } else if (it != intervals.end() && it->first == idx) {
                int right = it->second;
                intervals.erase(it);
                intervals.insert({idx + 1, right});
            } else if (it != intervals.begin() && prev(it)->second == idx) {
                int left = prev(it)->first;
                intervals.erase(prev(it));
                intervals.insert({left, idx - 1});
            } else {
                int left = prev(it)->first;
                int right = prev(it)->second;
                intervals.erase(prev(it));
                intervals.insert({left, idx - 1});
                intervals.insert({idx + 1, right});
            }
        }

        cout << intervals.size() << "\n";
    }

    return 0;
}