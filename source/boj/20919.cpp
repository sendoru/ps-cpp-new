// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

class BinaryTrie {
    array<BinaryTrie *, 2> child;
    int count;

  public:
    BinaryTrie() : child{nullptr, nullptr}, count(0) {}
    bool find(int x, int bit = 30) {
        if (bit < 0)
            return count > 0;
        int b = (x >> bit) & 1;
        if (child[b] == nullptr)
            return false;
        return child[b]->find(x, bit - 1);
    }

    void insert(int x, int bit = 30) {
        count++;
        if (bit < 0)
            return;
        int b = (x >> bit) & 1;
        if (child[b] == nullptr)
            child[b] = new BinaryTrie();
        child[b]->insert(x, bit - 1);
    }

    int size() const {
        return count;
    }

    void erase(int x, int bit = 30) {
        count--;
        if (bit < 0)
            return;
        int b = (x >> bit) & 1;
        child[b]->erase(x, bit - 1);
        if (child[b]->count == 0) {
            delete child[b];
            child[b] = nullptr;
        }
    }

    int get_max_xor(int x, int bit = 30) {
        if (bit < 0)
            return 0;
        int b = (x >> bit) & 1;
        if (child[1 - b]) {
            return (1 << bit) + child[1 - b]->get_max_xor(x, bit - 1);
        } else {
            return child[b]->get_max_xor(x, bit - 1);
        }
    }

    int get_min_xor(int x, int bit = 30) {
        if (bit < 0)
            return 0;
        int b = (x >> bit) & 1;
        if (child[b]) {
            return child[b]->get_min_xor(x, bit - 1);
        } else {
            return (1 << bit) + child[1 - b]->get_min_xor(x, bit - 1);
        }
    }

    ~BinaryTrie() {
        for (int i = 0; i < 2; i++) {
            if (child[i])
                delete child[i];
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        BinaryTrie bt;
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            int v;
            cin >> v;
            if (!bt.find(v)) {
                bt.insert(v);
            }
        }
        while (q--) {
            int cmd;
            cin >> cmd;
            switch (cmd) {
            case 1: {
                int v;
                cin >> v;
                cout << bt.get_min_xor(v) << '\n';
                break;
            }
            case 2: {
                int v;
                cin >> v;
                cout << bt.get_max_xor(v) << '\n';
                break;
            }
            case 3: {
                int v;
                cin >> v;
                if (!bt.find(v)) {
                    bt.insert(v);
                }
                cout << bt.size() << '\n';
                break;
            }
            case 4: {
                int min_val = bt.get_min_xor(0);
                cout << min_val << '\n';
                bt.erase(min_val);
                break;
            }
            case 5: {
                int max_val = bt.get_max_xor(0);
                cout << max_val << '\n';
                bt.erase(max_val);
                break;
            }
            }
        }
        cout.flush();
    }

    return 0;
}