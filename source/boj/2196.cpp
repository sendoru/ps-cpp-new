// #include "atcoder/all"
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

    int b, e;
    cin >> b >> e;
    vector<int> a(e);
    for (int i = 0; i < e; i++) {
        cin >> a[i];
    }

    vector<int> dist(1 << b, -1);
    queue<int> q;
    for (int i = 0; i < e; i++) {
        dist[a[i]] = 0;
        q.push(a[i]);
    }

    return 0;
}