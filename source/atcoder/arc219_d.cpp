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

    ll t;
    cin >> t;
    while (t--) {
        ll n, k;
        cin >> n >> k;
        vector<vector<ll>> grid(n, vector<ll>(n));
        for (ll i = 0; i < n; i++) {
            for (ll j = 0; j < n; j++) {
                cin >> grid[i][j];
            }
        }

        // k == 1일땐 쉽다
        // 격자 위의 돌 하나는 님 게임에서 1개짜리 돌무더기 (r + c)개와 같다
        // 달리 말하면 (r + c) % 2 == 0인 위치의 돌은 게임에 영향을 안 준다.
        // (r + c) % 2 == 1인 위치의 돌을 한 칸 옮기면 (r + c) % 2 == 0이 되니까,
        // 사실상 게임에서 그 돌을 배제하는 것과 같다.

        // 그 다음으로 간단해 보이는 k == inf일 때도 생각해보자
        // (r, c) where (r + c) % 2 == 0에 돌이 a개 있다고 해 보자.
        // a == 0이면 그런디 수는 당연히 0이다.
        // a == 1이면 이 칸에서 동작을 취했을 때 다음 턴에는 그런디 수가 0이 된다. nxt = {0}, mex(nxt) = 1, 그런디 수는 1이다.
        // 대충 귀납적으로 생각하면 돌 a개의 그런디 수는 a이다.

        // k가 임의의 수일 때
        // a <= k일 때는 k가 행동을 제약하지 않으므로 그런디 수는 위와 마찬가지로 a이다.
        // a == k + 1일 때, 다음 턴에 있을 수 있는 돌 개수는 1, 2, ... k이다.
        // x <= k일 때 G(x) = k이므로 nxt = {1, 2, ..., k}이고 mex(nxt) = 0이므로 그런디 수는 0이다.
        // a == k + 2일 때, 다음 턴에 있을 수 있는 돌 개수는 2, 3, ... k + 1이다.
        // 비슷한 방법으로, nxt = {2, 3, ..., k, G(k + 1) = 0}, mex(nxt) = 1이므로 그런디 수는 1이다.

        // 일반화하면, G(a) = a % (k + 1)인 것 같다.

        ll grundy = 0;
        for (ll r = 0; r < n; r++) {
            for (ll c = 0; c < n; c++) {
                if ((r + c) & 1) {
                    grundy ^= grid[r][c] % (k + 1);
                }
            }
        }

        cout << (grundy ? "Alice" : "Bob") << "\n";
    }

    return 0;
}