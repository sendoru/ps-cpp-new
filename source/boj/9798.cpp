// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Node {
    int idx, k, a, parent, left, right;
    Node() {}
    Node(int idx, int k, int a) : idx(idx), k(k), a(a) {
        parent = -1;
        left = -1;
        right = -1;
    }

    bool operator<(const Node &other) const {
        return k < other.k;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<Node> nodes(n);
    for (int i = 0; i < n; i++) {
        int k, a;
        cin >> k >> a;
        nodes[i] = Node(i, k, a);
    }

    sort(nodes.begin(), nodes.end(), [](const Node &a, const Node &b) {
        return a.a < b.a;
    });

    set<Node> s;
    s.insert(nodes[0]);
    bool possible = true;
    for (int i = 1; i < n && possible; i++) {
        auto it = s.lower_bound(nodes[i]);
        // nodes[i] is the smallest
        if (it == s.begin()) {
            // cannot add nodes[i] to the set
            // if first node in s has left child
            if (it->left != -1) {
                possible = false;
                break;
            }
            Node parent = *it;
            s.erase(it);
            parent.left = nodes[i].idx;
            nodes[i].parent = parent.idx;
            s.insert(parent);
        } else if (it == s.end()) {
            it--;
            if (it->right != -1) {
                possible = false;
                break;
            }
            Node parent = *it;
            s.erase(it);
            parent.right = nodes[i].idx;
            nodes[i].parent = parent.idx;
            s.insert(parent);
        } else {
            Node left_parent = *prev(it);
            Node right_parent = *it;
            if (right_parent.left == -1) {
                s.erase(right_parent);
                right_parent.left = nodes[i].idx;
                nodes[i].parent = right_parent.idx;
                s.insert(right_parent);
            } else if (left_parent.right == -1) {
                s.erase(left_parent);
                left_parent.right = nodes[i].idx;
                nodes[i].parent = left_parent.idx;
                s.insert(left_parent);
            } else {
                possible = false;
                break;
            }
        }

        s.insert(nodes[i]);
    }

    vector<array<int, 3>> ans(n);
    for (auto &node : s) {
        ans[node.idx][0] = node.parent;
        ans[node.idx][1] = node.left;
        ans[node.idx][2] = node.right;
    }

    if (!possible) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for (int i = 0; i < n; i++) {
            cout << ans[i][0] + 1 << ' ' << ans[i][1] + 1 << ' ' << ans[i][2] + 1 << '\n';
        }
    }

    return 0;
}