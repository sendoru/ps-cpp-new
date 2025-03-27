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
    cout << fixed << setprecision(12);

    ll x, y, d, t;
    cin >> x >> y >> d >> t;

    double dist = sqrt(x * x + y * y);
    double ans = dist;
    // d/t <= 1이면 무조건 최소 시간은 dist
    if (d <= t) {
        cout << ans << '\n';
        return 0;
    }
    ll k = (dist + 1e-9) / d;
    // (1) 원점까지 직선으로 k번 점프 후 남을 거리 걸어가기
    ans = min(ans, k * t + dist - k * d);
    // (2-1) k == 0일때, 원점까지 직선으로 1번 점프 후 초과된 걸이 걸어서 돌아오기
    if (k == 0) {
        ans = min(ans, t + d - dist);
        // 또는 2번 잘 점프
        ans = min(ans, 2. * t);
    }
    // (2-2) k != 0일 때, k + 1번 잘 점프해서 점프로만 가기
    else {
        ans = min(ans, (double)(k + 1) * t);
    }

    cout << ans << '\n';

    return 0;
}