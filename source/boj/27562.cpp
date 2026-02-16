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
    array<Trie *, 26> next;
    bool is_end;
    // count of the number of strings that pass through this node
    int count;

    Trie() {
        next.fill(nullptr);
        is_end = false;
        count = 0;
    }

    void insert(const string &s) {
        Trie *cur = this;
        for (char c : s) {
            cur->count++;
            int idx = c - 'a';
            if (cur->next[idx] == nullptr) {
                cur->next[idx] = new Trie();
            }
            cur = cur->next[idx];
        }
        cur->is_end = true;
        cur->count++;
    }

    void remove(const string &s) {
        Trie *cur = this;
        for (char c : s) {
            cur->count--;
            int idx = c - 'a';
            if (cur->next[idx] == nullptr) {
                return;
            }
            cur = cur->next[idx];
        }
        cur->is_end = false;
        cur->count--;
    }

    vector<int> counts(const string &s) {
        Trie *cur = this;
        vector<int> res(s.size() + 1);
        int res_idx = 0;
        for (char c : s) {
            res[res_idx] = cur->count;
            int idx = c - 'a';
            if (cur->next[idx] == nullptr) {
                return res;
            }
            cur = cur->next[idx];
            res_idx++;
        }
        res[res_idx] = cur->count;
        return res;
    }

    ~Trie() {
        for (Trie *nxt : next) {
            if (nxt != nullptr) {
                delete nxt;
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    array<Trie, 2> tries;
    int q;
    cin >> q;
    while (q--) {
        string op;
        cin >> op;
        if (op == "add") {
            string t, s;
            cin >> t >> s;
            if (t == "B") {
                reverse(s.begin(), s.end());
            }
            tries[t[0] - 'A'].insert(s);
        } else if (op == "delete") {
            string t, s;
            cin >> t >> s;
            if (t == "B") {
                reverse(s.begin(), s.end());
            }
            tries[t[0] - 'A'].remove(s);
        } else if (op == "find") {
            string s;
            cin >> s;
            vector<int> cnt_a = tries[0].counts(s);
            reverse(s.begin(), s.end());
            vector<int> cnt_b = tries[1].counts(s);
            ll ans = 0;
            for (int i = 1; i < cnt_a.size() - 1; i++) {
                ans += (ll)cnt_a[i] * cnt_b[cnt_b.size() - 1 - i];
            }
            cout << ans << "\n";
        }
    }

    return 0;
}