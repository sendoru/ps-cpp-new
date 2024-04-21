#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }

    vector<int> pos(n);
    for (int i = 0; i < n; i++) {
        pos[a[i]] = i;
    }

    vector<pii> swap_order;
    // make ith element to i
    for (int i = 0; i < n; i++) {
        if (a[i] != i) {
            swap_order.push_back({i, pos[i]});
            if (swap_order.back().first > swap_order.back().second) {
                swap(swap_order.back().first, swap_order.back().second);
            }
            int temp = a[i];
            swap(a[i], a[pos[i]]);
            swap(pos[i], pos[temp]);
        }
    }

    cout << swap_order.size() << '\n';
    for (auto elem : swap_order) {
        cout << elem.first + 1 << ' ' << elem.second + 1 << '\n';
    }

    return 0;
}

/*
6
1 6 2 5 3 4
5
2 3 -> 1 2 6 5 3 4 (pos: 0 1 4 5 3 2)
3 5 -> 1 2 3 5 6 4 (pos: 0 1 2 5 3 4)
4 6 -> 1 2 3 4 6 5 (pos: 0 1 2 3 5 4)
5 6 -> 1 2 3 4 5 6 (pos: 0 1 2 3 4 5)
*/