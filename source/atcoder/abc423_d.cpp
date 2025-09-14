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

    ll n, k;
    cin >> n >> k;
    vector<array<ll, 3>> abc(n);
    for (int i = 0; i < n; i++) {
        cin >> abc[i][0] >> abc[i][1] >> abc[i][2];
    }

    priority_queue<pll, vector<pll>, greater<pll>> pq;
    ll cur_time = 0;
    for (int i = 0; i < n; i++) {
        // 자리 날 때까지 pq에서 pop
        while (!pq.empty() && k < abc[i][2]) {
            auto [end_time, cnt] = pq.top();
            pq.pop();
            k += cnt;
            cur_time = end_time;
        }
        if (cur_time < abc[i][0]) {
            cur_time = abc[i][0];
        }
        pq.push({cur_time + abc[i][1], abc[i][2]});
        k -= abc[i][2];
        cout << cur_time << '\n';
    }

    return 0;
}

/*
279290
1094410
1314176
1897674
1921802
7691643
7822368
8528921
8528921
10549857

279290
1094410
1314176
1897674
1921802
7691643
7822368
8528921
8528921
10549857
*/