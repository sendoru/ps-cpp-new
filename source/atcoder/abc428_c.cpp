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

    int q;
    cin >> q;
    int error_pos = -1;
    int cur_state = 0;
    string s;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            char c;
            cin >> c;
            s.push_back(c);
            if (c == '(') {
                cur_state++;
            } else {
                cur_state--;
                if (cur_state < 0 && error_pos == -1) {
                    error_pos = (int)s.size() - 1;
                }
            }
        } else {
            char c = s.back();
            s.pop_back();
            if (c == '(') {
                cur_state--;
            } else {
                cur_state++;
                if (error_pos == (int)s.size()) {
                    error_pos = -1;
                }
            }
        }

        if (error_pos == -1 && cur_state == 0) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}