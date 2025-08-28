// #include "atcoder/all"
#pragma GCC optimize("Ofast")
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

    vector<int> fibs = {1, 1};
    while (fibs.back() <= 3e6) {
        fibs.push_back(fibs[fibs.size() - 1] + fibs[fibs.size() - 2]);
    }
    vector<int> grundy(3e6 + 10);
    // grundy[0] = 0
    for (int i = 1; i < grundy.size(); i++) {
        array<bool, 40> check = {};
        for (int j = 0; j < fibs.size() && fibs[j] <= i; j++) {
            check[grundy[i - fibs[j]]] = true;
        }
        while (check[grundy[i]]) {
            grundy[i]++;
        }
    }

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll xor_sum = 0;
    for (int i = 0; i < n; i++) {
        xor_sum ^= grundy[a[i]];
    }

    cout << (xor_sum == 0 ? "cubelover" : "koosaga");

    return 0;
}