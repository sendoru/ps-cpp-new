#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll n;
    cin >> n;
    vector<pair<ll, ll>> S;
    int q, k = 0;
    cin >> q;
    while (q--) {
        ll P, Q;
        cin >> P >> Q;
        if (P > Q)
            swap(P, Q);
        int z = 2;
        for (auto [a, b] : S) {
            if ((a < P && P < b) ^ (a < Q && Q < b))
                z--;
            if (a == P || b == P)
                z = 0;
            if (a == Q || b == Q)
                z = 0;
        }
        if (z > 0)
            S.emplace_back(P, Q), k++;
        else
            break;
    }
    cout << k;
}