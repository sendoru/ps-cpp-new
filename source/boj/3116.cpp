#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Bacteria {
    int x, y, dir, dir_x, dir_y;

    // class variable
    static const int dx[8];
    static const int dy[8];

    Bacteria(int x, int y, int dir) : x(x), y(y), dir(dir) {
        dir_x = dx[dir];
        dir_y = dy[dir];
    }
};

struct txy {
    int t, x, y;
    txy(int t, int x, int y) : t(t), x(x), y(y) {}
    bool operator<(const txy &rhs) const {
        if (t != rhs.t)
            return t < rhs.t;
        if (x != rhs.x)
            return x < rhs.x;
        return y < rhs.y;
    }
};

const int Bacteria::dx[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
const int Bacteria::dy[8] = {1, 1, 1, 0, -1, -1, -1, 0};

vector<int> get_cross(const Bacteria &a, const Bacteria &b) {
    int d0 = max(abs(a.x - b.x), abs(a.y - b.y));
    int d1 = max(abs(a.x + a.dir_x - b.x - b.dir_x),
                 abs(a.y + a.dir_y - b.y - b.dir_y));

    if (d1 >= d0 || d0 % (d0 - d1) != 0)
        return {-1, -1, -1};

    int t = d0 / (d0 - d1);
    if (a.x + t * a.dir_x == b.x + t * b.dir_x &&
        a.y + t * a.dir_y == b.y + t * b.dir_y) {
        return {a.x + t * a.dir_x, a.y + t * a.dir_y, t};
    }

    return {-1, -1, -1};
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<Bacteria> bacteria;
    for (int i = 0; i < n; i++) {
        int x, y, dir;
        cin >> x >> y >> dir;
        dir--;
        bacteria.emplace_back(x, y, dir);
    }

    map<txy, int> cross_cnt;

    vector<int> cross_cnt_by_t(2'000'100);
    vector<int> t_used;

    int max_k = 0, min_t = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            auto cross = get_cross(bacteria[i], bacteria[j]);
            if (cross[2] != -1) {
                cross_cnt_by_t[cross[2]]++;
                t_used.push_back(cross[2]);
                if (cross_cnt_by_t[cross[2]] + 1 > max_k || (cross_cnt_by_t[cross[2]] + 1 == max_k && cross[2] < min_t)) {
                    max_k = cross_cnt_by_t[cross[2]] + 1;
                    min_t = cross[2];
                }
            }
        }
        for (int t : t_used) {
            cross_cnt_by_t[t] = 0;
        }
        t_used.clear();
    }

    cout << max_k << '\n'
         << min_t << '\n';

    return 0;
}