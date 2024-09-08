// #include "atcoder/all"
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

    int n, m, k;
    cin >> n >> m >> k;

    vector<bool> used(4 * n + 1, false);
    used[0] = true;

    for (int i = 0; i < 2 * m; i++) {
        int x;
        cin >> x;
        used[x] = true;
    }

    int a, b;

    cin >> a >> b;
    int score = abs((a % k) - (b % k));
    used[a] = true;
    used[b] = true;

    vector<int> remain_cnt(k);
    for (int i = 0; i <= 4 * n; i++) {
        if (!used[i]) {
            remain_cnt[i % k]++;
        }
    }

    int ans = 0;
    int cur = 0;

    for (int i = score + 1; i < k; i++) {
        // cur : mod k가 i인 카드와 매칭시킬 수 있는 카드의 갯수
        cur += remain_cnt[i - score - 1];
        ans += min(cur, remain_cnt[i]);
        // 매칭된 min(cur, remain_cnt[i]) 개는 더 이상 사용할 수 없음
        cur -= min(cur, remain_cnt[i]);
    }

    cout << min(m - 1, ans) << '\n';

    return 0;
}