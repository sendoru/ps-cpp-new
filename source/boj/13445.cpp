// #include "atcoder/all"
#include <bits/stdc++.h>
// #define DEBUG

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Trie {
    vector<Trie *> child;
    bool terminal;
    int cnt;

    Trie() : cnt(0) {
        child.resize(2, nullptr);
    }
    ~Trie() {
        for (auto c : child) {
            if (c) {
                delete c;
            }
        }
    }

    void insert(string &s, int idx) {
        if (idx == s.size()) {
            terminal = true;
            cnt++;
            return;
        }

        int next = s[idx] - '0';
        if (!child[next]) {
            child[next] = new Trie();
        }
        child[next]->insert(s, idx + 1);
    }

    void xor_to_elements(string &s, int idx) {
        if (idx == s.size()) {
            return;
        }
        if (s[idx] == '1') {
            // swap child[0] and child[1]
            swap(child[0], child[1]);
        }
        if (child[0])
            child[0]->xor_to_elements(s, idx + 1);
        if (child[1])
            child[1]->xor_to_elements(s, idx + 1);
    }

    // int query(string &s, int idx) {
    //     if (idx == s.size()) {
    //         return 0;
    //     }

    //     int next = s[idx] - '0';
    //     if (child[next] && child[next]->cnt > 0) {
    //         return child[next]->query(s, idx + 1);
    //     } else {
    //         return (1 << (30 - idx)) + child[1 - next]->query(s, idx + 1);
    //     }
    // }

    int find_smaller_than_s(string &s, int idx) {
        if (idx == s.size()) {
            return 0;
        }

        int next = s[idx] - '0';
        if (next == 0) {
            return child[0] ? child[0]->find_smaller_than_s(s, idx + 1) : 0;
        } else {
            int ret = 0;
            if (child[0]) {
                ret += child[0]->cnt;
            }
            if (child[1]) {
                ret += child[1]->find_smaller_than_s(s, idx + 1);
            }
            return ret;
        }
    }
};

string to_binary(int n) {
    string ret;
    for (int i = 0; i < 21; i++) {
        ret += to_string(n & 1);
        n >>= 1;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

int to_int(string s) {
    int ret = 0;
    for (int i = 0; i < s.size(); i++) {
        ret <<= 1;
        ret += s[i] - '0';
    }
    return ret;
}

ll solve_naive(vector<ll> &a, ll k) {
    ll ans = 0;
    for (int i = 0; i < a.size(); i++) {
        ll cur = 0;
        for (int j = i; j < a.size(); j++) {
            cur ^= a[j];
            if (cur < k) {
                ans++;
            }
        }
    }

    return ans;
}

ll solve(vector<ll> &a, ll k) {
    ll ans = 0;
    Trie *root = new Trie();
    string k_bin = to_binary(k);

    for (int i = 0; i < a.size(); i++) {
        string s = to_binary(a[i]);
        root->xor_to_elements(s, 0);
        root->insert(s, 0);
        ans += root->find_smaller_than_s(k_bin, 0);
    }

    return ans;
}

bool test() {
    bool ret = true;
    for (int i = 0; i < 333; i++) {
        vector<ll> a(333);
        for (int j = 0; j < 333; j++) {
            a[j] = rand() % 123456;
        }
        ll k = rand() % 123456;
        ll naive = solve_naive(a, k);
        ll trie = solve(a, k);
        if (naive != trie) {
            cout << "Expected: " << naive << ", Got: " << trie << "\n";
            ret = false;
        }
    }
    cout << "Done" << "\n";
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifndef DEBUG
    int n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    // vector<string> a_bin(n);
    // for (int i = 0; i < n; i++) {
    //     a_bin[i] = to_binary(a[i]);
    // }

    cout << solve(a, k) << "\n";
#endif

#ifdef DEBUG
    test();
#endif

    return 0;
}