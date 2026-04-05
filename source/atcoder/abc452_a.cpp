// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<array<int, 2>> G = {
    {1, 7},
    {3, 3},
    {5, 5},
    {7, 7},
    {9, 9}};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int m, d;
    cin >> m >> d;
    if (find(G.begin(), G.end(), array<int, 2>{m, d}) != G.end()) {
        cout << "Yes";
    } else {
        cout << "No";
    }

    return 0;
}