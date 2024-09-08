// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> move(n);
    for (int i = 0; i < n; i++) {
        cin >> move[i];
    }
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }

    vector<int> ans;
    int cur_idx = 0;
    while (!move.empty()) {
        ans.push_back(a[cur_idx] + 1);
        int move_val = move[cur_idx] - (move[cur_idx] > 0 ? 1 : 0);
        a.erase(a.begin() + cur_idx);
        move.erase(move.begin() + cur_idx);
        if (move.empty()) {
            break;
        }
        cur_idx = (cur_idx + move_val + 20000 * a.size()) % a.size();
    }

    for (int elem : ans) {
        cout << elem << ' ';
    }

    return 0;
}