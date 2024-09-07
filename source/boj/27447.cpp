// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> actions(1'000'001);

    // serve
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        actions[tmp] = 3;
    }

    // make coffee
    int cnt = 0;
    for (int i = actions.size() - 1; i >= 0; i--) {
        if (actions[i] == 3) {
            cnt++;
        } else if (cnt > 0) {
            actions[i] = 2;
            cnt--;
        }
    }

    if (cnt > 0) {
        cout << "fail";
        return 0;
    }

    cnt = n;

    for (int i = 0; i < actions.size(); i++) {
        if (actions[i] == 0) {
            actions[i] = 1;
            cnt--;
            if (cnt == 0) {
                break;
            }
        }
    }

    // check 1: coffee is served before m seconds elapse after the coffee is made

    vector<int> action_2, action_3;
    for (int i = 0; i < actions.size(); i++) {
        if (actions[i] == 2) {
            action_2.push_back(i);
        } else if (actions[i] == 3) {
            action_3.push_back(i);
        }
    }

    for (int i = 0; i < action_2.size(); i++) {
        if (action_2[i] + m < action_3[i]) {
            cout << "fail";
            return 0;
        }
    }

    // check 2: an empty cup exists before the coffee is made

    int cup_cnt = 0;
    for (int i = 0; i < actions.size(); i++) {
        if (actions[i] == 1) {
            cup_cnt++;
        } else if (actions[i] == 2) {
            if (cup_cnt == 0) {
                cout << "fail";
                return 0;
            }
            cup_cnt--;
        }
    }

    cout << "success";

    return 0;
}