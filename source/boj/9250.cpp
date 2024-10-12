// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

// Trie with Aho-Corasick
class Trie {
  public:
    struct Node {
        int child[26];
        int fail;
        vector<int> output;
        Node() {
            fill(child, child + 26, -1);
            fail = 0;
        }
    };
    vector<Node> trie;
    int root;
    int num_words;
    Trie() {
        trie.push_back(Node());
        root = 0;
        num_words = 0;
    }

    // return the index of the inserted string
    void insert(const string &s) {
        int node = root;
        for (char c : s) {
            int next = c - 'a';
            if (trie[node].child[next] == -1) {
                trie[node].child[next] = trie.size();
                trie.push_back(Node());
            }
            node = trie[node].child[next];
        }
        trie[node].output.push_back(num_words);
        num_words++;
    }

    

    // build fail link
    void build() {
        queue<int> q;
        q.push(root);
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (int i = 0; i < 26; i++) {
                int next = trie[node].child[i];
                if (next == -1) {
                    continue;
                }
                if (node == root) {
                    trie[next].fail = root;
                } else {
                    int x = trie[node].fail;
                    while (x != root && trie[x].child[i] == -1) {
                        x = trie[x].fail;
                    }
                    if (trie[x].child[i] != -1) {
                        x = trie[x].child[i];
                    }
                    trie[next].fail = x;
                }
                for (int &output : trie[trie[next].fail].output) {
                    trie[next].output.push_back(output);
                }
                q.push(next);
            }
        }
    }

    // ret[i] = 1 if s contains i-th string
    vector<int> match(const string &s) {
        vector<int> ret(num_words);
        int node = root;
        for (char c : s) {
            int next = c - 'a';
            while (node != root && trie[node].child[next] == -1) {
                node = trie[node].fail;
            }
            if (trie[node].child[next] != -1) {
                node = trie[node].child[next];
            }
            for (int output : trie[node].output) {
                ret[output] = 1;
            }
        }
        return ret;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    Trie trie;
    vector<string> words(n);
    vector<int> word_idx(n);
    for (int i = 0; i < n; i++) {
        cin >> words[i];
        trie.insert(words[i]);
    }

    trie.build();

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s;
        vector<int> ret = trie.match(s);
        bool ok = false;
        for (int j : ret) {
            if (j) {
                ok = true;
                break;
            }
        }

        cout << (ok ? "YES" : "NO") << '\n';
    }

    return 0;
}