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

    while (true) {
        int l, a;
        cin >> l >> a;
        if (!cin.good()) {
            break;
        }

        vector<int> left, right, all;
        for (int i = 0; i < a; i++) {
            char c;
            int x;
            cin >> x >> c;
            if (c == 'L') {
                left.push_back(x);
            } else {
                right.push_back(x);
            }
            all.push_back(x);
        }
        sort(left.begin(), left.end());
        sort(right.begin(), right.end());
        sort(all.begin(), all.end());
        int left_time = left.size() > 0 ? left.back() : -1;
        int right_time = right.size() > 0 ? l - right.front() : -1;
        if (left_time > right_time) {
            cout << format("The last ant will fall down in {} seconds - started at {}.", left_time, all[left.size() - 1]) << '\n';
        } else if (right_time > left_time) {
            cout << format("The last ant will fall down in {} seconds - started at {}.", right_time, all[a - right.size()]) << '\n';
        } else {
            cout << format("The last ant will fall down in {} seconds - started at {} and {}.", left_time, all[left.size() - 1], all[a - right.size()]) << '\n';
        }
    }

    return 0;
}