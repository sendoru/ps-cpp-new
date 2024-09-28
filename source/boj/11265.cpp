// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> dist(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dist[i][j];
        }
    }

    for (int mid = 0; mid < n; mid++) {
        for (int s = 0; s < n; s++) {
            for (int e = 0; e < n; e++) {
                if (dist[s][e] > dist[s][mid] + dist[mid][e]) {
                    dist[s][e] = dist[s][mid] + dist[mid][e];
                }
            }
        }
    }

    for (int i = 0; i < m; i++) {
        int s, e, t;
        cin >> s >> e >> t;
        cout << (dist[s - 1][e - 1] <= t ? "Enjoy other party" : "Stay here") << '\n';
    }

    return 0;
}