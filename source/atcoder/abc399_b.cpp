// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<pii> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].first;
        p[i].second = i;
    }

    sort(p.begin(), p.end(), greater<pii>());
    vector<int> ans(n);
    ans[0] = 1;
    for (int i = 1; i < n; i++) {
        if (p[i].first == p[i - 1].first) {
            ans[i] = ans[i - 1];
        }
        else {
            ans[i] = i + 1;
        }
    }

    for (int i = 0; i < n; i++) {
        p[i].first = ans[i];
    }

    sort(p.begin(), p.end(), [](pii a, pii b) {
        return a.second < b.second;
    });

    for (int i = 0; i < n; i++) {
        cout << p[i].first << "\n";
    }

    return 0;
}