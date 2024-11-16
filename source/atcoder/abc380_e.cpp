#include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Dsu {
    int n;
    vector<int> parent;
    vector<int> left_end;
    vector<int> right_end;
    vector<int> color;
    vector<int> color_cnt;

    Dsu(int n) : n(n)
    {
        parent.resize(n);
        left_end.resize(n);
        right_end.resize(n);
        color.resize(n);
        color_cnt.resize(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            color[i] = i;
            left_end[i] = i;
            right_end[i] = i;
        }
    }

    int find(int x)
    {
        if (x == parent[x]) {
            return x;
        }
        else {
            return parent[x] = find(parent[x]);
        }
    }

    void unite(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b) {
            return;
        }
        if (a > b) {
            swap(a, b);
        }
        parent[b] = a;
        left_end[a] = min(left_end[a], left_end[b]);
        right_end[a] = max(right_end[a], right_end[b]);
    }

    int get_size(int x)
    {
        x = find(x);
        return right_end[x] - left_end[x] + 1;
    }

    int get_color(int x)
    {
        return color[find(x)];
    }

    void change_color(int x, int c)
    {
        x = find(x);
        int old_color = get_color(x);
        color_cnt[old_color] -= get_size(x);
        color_cnt[c] += get_size(x);
        color[x] = c;
        // unite adj nodes with same color
        if (left_end[x] > 0 && get_color(left_end[x] - 1) == c) {
            unite(x, find(left_end[x] - 1));
        }
        if (right_end[x] < n - 1 && get_color(right_end[x] + 1) == c) {
            unite(x, find(right_end[x] + 1));
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q;
    cin >> n >> q;
    Dsu dsu(n + 1);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, c;
            cin >> x >> c;
            dsu.change_color(x, c);
        }
        else {
            int c;
            cin >> c;
            cout << dsu.color_cnt[c] << endl;
        }
    }

    return 0;
}

/*
5 9
1 1 2
1 2 3
1 3 4
1 4 5
2 1
2 2
2 3
2 4
2 5

0
0
0
0
5
*/

/*
5 8
1 1 2
1 2 3
1 3 4
2 1
2 2
2 3
2 4
2 5

0
0
0
4
1
*/

/*
5 8
1 1 2
1 3 4
1 4 5
2 1
2 2
2 3
2 4
2 5

0
2
0
0
3
*/