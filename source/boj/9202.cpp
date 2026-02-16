// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<pii> dirs;

array<int, 9> scores = {
    0, 0, 0, 1, 1, 2, 3, 5, 11};

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
            int idx = c - 'A';
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
            int idx = c - 'A';
            if (cur->next[idx] == nullptr) {
                return;
            }
            cur = cur->next[idx];
        }
        cur->is_end = false;
        cur->count--;
    }

    bool find(const string &s) {
        Trie *cur = this;
        for (char c : s) {
            int idx = c - 'A';
            if (cur->next[idx] == nullptr) {
                return false;
            }
            cur = cur->next[idx];
        }
        return cur->is_end;
    }

    vector<int> counts(const string &s) {
        Trie *cur = this;
        vector<int> res(s.size() + 1);
        int res_idx = 0;
        for (char c : s) {
            res[res_idx] = cur->count;
            int idx = c - 'A';
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

    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) {
                continue;
            }
            dirs.emplace_back(dr, dc);
        }
    }

    int n;
    cin >> n;
    vector<string> words(n);
    for (int i = 0; i < n; i++) {
        cin >> words[i];
    }

    int t;
    cin >> t;
    while (t--) {
        vector<string> grid(4);
        for (int i = 0; i < 4; i++) {
            cin >> grid[i];
        }

        vector<string> found_words;
        // dfs
        vector<vector<bool>> visited(4, vector<bool>(4));

        function<void(int, int, string)> dfs = [&](int r, int c, string cur) {
            if (cur.size() >= 1) {
                found_words.push_back(cur);
            }
            if (cur.size() == 8) {
                return;
            }
            visited[r][c] = true;
            for (pii dir : dirs) {
                int nr = r + dir.first;
                int nc = c + dir.second;
                if (nr < 0 || nr >= 4 || nc < 0 || nc >= 4) {
                    continue;
                }
                if (visited[nr][nc]) {
                    continue;
                }
                dfs(nr, nc, cur + grid[nr][nc]);
            }
            visited[r][c] = false;
        };

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                dfs(i, j, string(1, grid[i][j]));
            }
        }

        Trie trie;
        for (const string &w : found_words) {
            trie.insert(w);
        }

        int score = 0;
        string longest;
        int found = 0;
        for (const string &w : words) {
            if (trie.find(w)) {
                found++;
                score += scores[w.size()];
                if (w.size() > longest.size()) {
                    longest = w;
                } else if (w.size() == longest.size() && w < longest) {
                    longest = w;
                }
            }
        }

        cout << score << ' ' << longest << ' ' << found << '\n';
    }

    return 0;
}