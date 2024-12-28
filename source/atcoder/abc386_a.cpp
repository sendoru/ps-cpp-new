// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

bool check(vector<int> &v)
{
    if (v[0] < v[1] && v[1] == v[2] && v[2] == v[3]) {
        return true;
    }
    if (v[0] == v[1] && v[1] < v[2] && v[2] == v[3]) {
        return true;
    }
    if (v[0] == v[1] && v[1] == v[2] && v[2] < v[3]) {
        return true;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<int> v(4);
    for (int i = 0; i < 4; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    cout << (check(v) ? "Yes" : "No") << '\n';

    return 0;
}