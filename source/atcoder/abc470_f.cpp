// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll b, ll e, ll m) {
    ll res = 1;
    while (e) {
        if (e & 1)
            res = res * b % m;
        b = b * b % m;
        e >>= 1;
    }
    return res;
}

ll modinv(ll a, ll m) {
    return modpow(a, m - 2, m);
}

struct Dsu {
    int n;
    vector<int> parent;
    vector<int> size;

    Dsu(int n) : n(n), parent(n), size(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        if (size[x] < size[y])
            swap(x, y);
        parent[y] = x;
        size[x] += size[y];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<ll> fact(200010, 1), inv_fact(200010, 1);
    for (int i = 1; i < 200010; i++) {
        fact[i] = fact[i - 1] * i % MOD9;
    }
    inv_fact[200009] = modinv(fact[200009], MOD9);
    for (int i = 200008; i >= 0; i--) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD9;
    }

    ll n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    Dsu dsu(n);
    vector<array<ll, 2>> ab(m);
    for (int i = 0; i < m; i++) {
        cin >> ab[i][0] >> ab[i][1];
        ab[i][0]--;
        ab[i][1]--;
    }

    ll ans = 1;
    for (int i = 0; i < m; i++) {
        dsu.unite(ab[i][0], ab[i][1]);
    }
    vector<vector<int>> groups(n);
    for (int i = 0; i < n; i++) {
        groups[dsu.find(i)].push_back(i);
    }

    bool has_same = false;
    for (int i = 0; i < n; i++) {
        if (groups[i].size() > 1) {
            map<char, int> cnt;
            for (int j : groups[i]) {
                cnt[s[j]]++;
                if (cnt[s[j]] > 1) {
                    has_same = true;
                }
            }
            ans = ans * fact[groups[i].size()] % MOD9;
            for (auto [k, v] : cnt) {
                ans = ans * inv_fact[v] % MOD9;
            }
        }
    }

    if (has_same) {
        cout << ans;
    } else {
        cout << ans * modinv(2, MOD9) % MOD9;
    }

    return 0;
}