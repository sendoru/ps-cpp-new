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

    array<int, 9> board;
    for (int i = 0; i < 9; i++) {
        cin >> board[i];
    }

    // bfs
    queue<pair<array<int, 9>, int>> q;
    map<array<int, 9>, int> dist;
    dist[board] = 0;
    q.push({board, 0});
    array<int, 9> goal = {1, 2, 3, 4, 5, 6, 7, 8, 0};

    while (!q.empty()) {
        auto [cur, d] = q.front();
        q.pop();
        int zero_pos = find(cur.begin(), cur.end(), 0) - cur.begin();
        int x = zero_pos / 3;
        int y = zero_pos % 3;
        vector<pair<int, int>> next_pos = {{x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}};
        for (auto [nx, ny] : next_pos) {
            if (nx < 0 || nx >= 3 || ny < 0 || ny >= 3) {
                continue;
            }
            array<int, 9> next = cur;
            swap(next[zero_pos], next[nx * 3 + ny]);
            if (!dist.count(next)) {
                dist[next] = d + 1;
                q.push({next, d + 1});
            }
        }
    }

    if (dist.count(goal)) {
        cout << dist[goal];
    } else {
        cout << -1;
    }

    return 0;
}