// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Trie {
    vector<vector<int>> next;
    vector<int> end_count;
    int size = 0;

    Trie() {
        next.resize(26, vector<int>(26, -1));
        end_count.resize(26, 0);
    }

    void insert(const string &s) {
        int node = 0;
        for (char c : s) {
            int idx = c - 'a';
            if (next[node][idx] == -1) {
                next[node][idx] = next.size();
                next.push_back(vector<int>(26, -1));
                end_count.push_back(0);
            }
            node = next[node][idx];
        }
        end_count[node]++;
        size++;
    }

    bool find(const string &s) {
        int node = 0;
        for (char c : s) {
            int idx = c - 'a';
            if (next[node][idx] == -1) {
                return false;
            }
            node = next[node][idx];
        }
        return end_count[node] > 0;
    }

    // finds if trie has prefix of s
    bool has_prefix(const string &s) {
        int node = 0;
        for (char c : s) {
            int idx = c - 'a';
            if (next[node][idx] == -1) {
                return false;
            }
            node = next[node][idx];
            if (end_count[node] > 0) {
                return true;
            }
        }
        return false;
    }

    void erase_with_prefix(const string &s) {
        int node = 0;
        for (char c : s) {
            int idx = c - 'a';
            if (next[node][idx] == -1) {
                return;
            }
            node = next[node][idx];
        }

        function<void(int)> dfs = [&](int node) {
            if (end_count[node] > 0) {
                size -= end_count[node];
                end_count[node] = 0;
            }
            for (int i = 0; i < 26; i++) {
                if (next[node][i] != -1) {
                    dfs(next[node][i]);
                }
            }
        };
        dfs(node);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    Trie trie_x, trie_y;

    int q;
    cin >> q;
    while (q--) {
        int t;
        cin >> t;
        string s;
        cin >> s;

        if (t == 1) {
            trie_x.insert(s);
            trie_y.erase_with_prefix(s);
        } else {
            if (!trie_x.has_prefix(s)) {
                trie_y.insert(s);
            }
        }
        cout << trie_y.size << '\n';
    }

    return 0;
}