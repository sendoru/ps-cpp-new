// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const vector<vector<int>> three = {
    {0, 1, 2},
    {0, 2, 4},
    {0, 4, 3},
    {0, 3, 1},
    {5, 1, 2},
    {5, 2, 4},
    {5, 4, 3},
    {5, 3, 1},
};

const vector<vector<int>> not_two = {
    {0, 5},
    {1, 4},
    {2, 3}};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<ll> dice(6);
    for (int i = 0; i < 6; i++) {
        cin >> dice[i];
    }
    if (n == 1) {
        cout << accumulate(dice.begin(), dice.end(), 0LL) - *max_element(dice.begin(), dice.end());
    } else {
        ll three_min = LLONG_MAX, two_min = LLONG_MAX, one_min = *min_element(dice.begin(), dice.end());
        for (const auto &arr : three) {
            ll sum = 0;
            for (int i : arr) {
                sum += dice[i];
            }
            three_min = min(three_min, sum);
        }
        for (int i = 0; i < 6; i++) {
            for (int j = i + 1; j < 6; j++) {
                if (i + j == 5) {
                    continue;
                }
                two_min = min(two_min, dice[i] + dice[j]);
            }
        }
        cout << three_min * 4 + two_min * 4 * (2 * n - 3) + one_min * ((n - 2) * (n - 2) + 4 * (n - 2) * (n - 1));
    }

    return 0;
}