// #include "atcoder/all"
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ll modpow(ll x, ll n, ll m) {
    ll ret = 1;
    while (n) {
        if (n & 1) {
            ret = ret * x % m;
        }
        x = x * x % m;
        n >>= 1;
    }
    return ret;
}

ll modinv(ll x, ll m) {
    return modpow(x, m - 2, m);
}

template <ll m = MOD1, ll p = 31>
struct SingleHashStr {
    ll hash, len;

    SingleHashStr() : hash(0), len(0) {}
    SingleHashStr(char c) : hash(c % m), len(1) {}
    SingleHashStr(char c, ll len) : len(len) {
        // c * (1 + p + p^2 + ... + p^(len - 1)) = c * (p^len - 1) / (p - 1)
        hash = c * (modpow(p, len, m) - 1) % m * modinv(p - 1, m) % m;
    }
    SingleHashStr(string s) {
        hash = 0;
        len = 0;
        for (char c : s) {
            *this = *this + c;
        }
    }
    SingleHashStr(const SingleHashStr<m, p> &rhs) {
        hash = rhs.hash;
        len = rhs.len;
    }
    SingleHashStr operator+(char c) const {
        SingleHashStr ret(*this);
        ret.hash = (ret.hash + c * modpow(p, len, m)) % m;
        ret.len++;
        return ret;
    }
    SingleHashStr operator+(const SingleHashStr &rhs) const {
        SingleHashStr ret(*this);
        ret.hash = (ret.hash + rhs.hash * modpow(p, len, m)) % m;
        ret.len += rhs.len;
        return ret;
    }
    bool operator==(const SingleHashStr &rhs) const {
        return hash == rhs.hash && len == rhs.len;
    }
    bool operator<(const SingleHashStr &rhs) const {
        return hash < rhs.hash || (hash == rhs.hash && len < rhs.len);
    }
};

template <ll m1 = MOD1, ll m2 = MOD9, ll p1 = 31, ll p2 = 37>
struct DoubleHashStr {
    ll hash1, hash2, len;

    DoubleHashStr() : hash1(0), hash2(0), len(0) {}
    DoubleHashStr(char c) : hash1(c % m1), hash2(c % m2), len(1) {}
    DoubleHashStr(char c, ll len) : len(len) {
        // c * (1 + p + p^2 + ... + p^(len - 1)) = c * (p^len - 1) / (p - 1)
        hash1 = c * (modpow(p1, len, m1) - 1) % m1 * modinv(p1 - 1, m1) % m1;
        hash2 = c * (modpow(p2, len, m2) - 1) % m2 * modinv(p2 - 1, m2) % m2;
        this->len = len;
    }
    DoubleHashStr(string s) {
        hash1 = 0;
        hash2 = 0;
        len = 0;
        for (char c : s) {
            *this = *this + c;
        }
    }
    DoubleHashStr(const DoubleHashStr<m1, m2, p1, p2> &rhs) {
        hash1 = rhs.hash1;
        hash2 = rhs.hash2;
        len = rhs.len;
    }
    DoubleHashStr operator+(char c) const {
        DoubleHashStr ret(*this);
        ret.hash1 = (ret.hash1 + c * modpow(p1, len, m1)) % m1;
        ret.hash2 = (ret.hash2 + c * modpow(p2, len, m2)) % m2;
        ret.len++;
        return ret;
    }
    DoubleHashStr operator+(const DoubleHashStr &rhs) const {
        DoubleHashStr ret(*this);
        ret.hash1 = (ret.hash1 + rhs.hash1 * modpow(p1, len, m1)) % m1;
        ret.hash2 = (ret.hash2 + rhs.hash2 * modpow(p2, len, m2)) % m2;
        ret.len += rhs.len;
        return ret;
    }
    bool operator==(const DoubleHashStr &rhs) const {
        return hash1 == rhs.hash1 && hash2 == rhs.hash2 && len == rhs.len;
    }
};

struct LazySegTree {
    int n;
    vector<SingleHashStr<>> tree;
    vector<char> lazy;
    vector<bool> is_lazy;

    LazySegTree(int n) {
        this->n = n;
        tree.resize(n * 4);
        lazy.resize(n * 4);
        is_lazy.resize(n * 4);
    }

    LazySegTree(string s) {
        n = s.length();
        tree.resize(n * 4);
        lazy.resize(n * 4);
        is_lazy.resize(n * 4);
        init(1, 0, n - 1, s);
    }

    SingleHashStr<> init(int node, int start, int end, string &s) {
        if (start == end) {
            return tree[node] = SingleHashStr<>(s[start]);
        } else {
            int mid = (start + end) / 2;
            return tree[node] = init(node * 2, start, mid, s) + init(node * 2 + 1, mid + 1, end, s);
        }
    }

    void propagate(int node, int s, int e) {
        if (is_lazy[node]) {
            if (s != e) {
                is_lazy[node * 2] = true;
                is_lazy[node * 2 + 1] = true;
                lazy[node * 2] = lazy[node];
                lazy[node * 2 + 1] = lazy[node];
            }
            tree[node] = SingleHashStr<>(lazy[node], e - s + 1);
            is_lazy[node] = false;
        }
    }

    void update(char c, int l, int r) {
        update(1, 0, n - 1, l, r, c);
    }

    void update(int node, int start, int end, int l, int r, char c) {
        propagate(node, start, end);
        if (r < start || end < l) {
            return;
        }
        if (l <= start && end <= r) {
            is_lazy[node] = true;
            lazy[node] = c;
            propagate(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        update(node * 2, start, mid, l, r, c);
        update(node * 2 + 1, mid + 1, end, l, r, c);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    SingleHashStr<> query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    SingleHashStr<> query(int node, int start, int end, int l, int r) {
        propagate(node, start, end);
        if (r < start || end < l) {
            return SingleHashStr<>();
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        return query(node * 2, start, mid, l, r) + query(node * 2 + 1, mid + 1, end, l, r);
    }
};

vector<vector<int>>
    perms = {
        {0}, {1}, {2}, {0, 1}, {0, 2}, {1, 0}, {1, 2}, {2, 0}, {2, 1}, {0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};

string conv(string s) {
    string ret;
    for (char c : s) {
        if (c == 'J') {
            ret.push_back(0);
        } else if (c == 'O') {
            ret.push_back(1);
        } else {
            ret.push_back(2);
        }
    }

    return ret;
}

string op(string s1, string s2) {
    string ret;
    for (int i = 0; i < s1.length(); i++) {
        ret.push_back((2 * s1[i] + 2 * s2[i]) % 3);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<string> s(3);
    for (int i = 0; i < 3; i++) {
        cin >> s[i];
        s[i] = conv(s[i]);
    }
    vector<string> s_combs;
    for (auto perm : perms) {
        string cur = s[perm[0]];

        for (int i = 1; i < perm.size(); i++) {
            cur = op(cur, s[perm[i]]);
        }

        s_combs.push_back(cur);
    }

    vector<SingleHashStr<>> s_comb_hashes;
    for (string &s_comb : s_combs) {
        s_comb_hashes.push_back(SingleHashStr<>(s_comb));
    }
    sort(s_comb_hashes.begin(), s_comb_hashes.end());

    int q;
    cin >> q;
    string t0;
    cin >> t0;
    t0 = conv(t0);
    LazySegTree st(t0);
    auto st_query = st.query(0, n - 1);
    auto lb = lower_bound(s_comb_hashes.begin(), s_comb_hashes.end(), st_query);
    if (lb != s_comb_hashes.end() && *lb == st_query) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        char c;
        cin >> l >> r >> c;
        if (c == 'J') {
            c = 0;
        } else if (c == 'O') {
            c = 1;
        } else {
            c = 2;
        }
        l--;
        r--;
        st.update(c, l, r);
        st_query = st.query(0, n - 1);
        lb = lower_bound(s_comb_hashes.begin(), s_comb_hashes.end(), st_query);
        if (lb != s_comb_hashes.end() && *lb == st_query) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}