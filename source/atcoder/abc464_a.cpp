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

    string s;
    cin >> s;
    int e_cnt = 0, w_cnt = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'E') {
            e_cnt++;
        }
        else {
            w_cnt++;
        }
    }

    cout << (e_cnt > w_cnt ? "East" : "West");

    return 0;
}