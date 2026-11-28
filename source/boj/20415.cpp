// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

map<char, int> mp = {
    {'B', 0},
    {'S', 1},
    {'G', 2},
    {'P', 3},
    {'D', 4},
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> thres(4);
    for (int i = 0; i < 4; i++) {
        cin >> thres[i];
    }
    string s;
    cin >> s;
    vector<int> hist(n);
    for (int i = 0; i < n; i++) {
        hist[i] = mp[s[i]];
    }

    vector<int> expand(n);
    if (hist[0] == 4) {
        expand[0] = thres[3];
    } else {
        expand[0] = thres[hist[0]] - 1;
    }

    for (int i = 1; i < n; i++) {
        if (hist[i] == 4) {
            expand[i] = thres[3];
        } else {
            expand[i] = thres[hist[i]] - 1 - expand[i - 1];
        }

        if (i == n - 1 || hist[i + 1] == 4) {
            continue;
        }

        if (thres[hist[i + 1]] - 1 < expand[i]) {
            expand[i] = thres[hist[i + 1]] - 1;
        }
    }

    cout << accumulate(expand.begin(), expand.end(), 0);

    return 0;
}