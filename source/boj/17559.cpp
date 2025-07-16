// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

struct Dot {
    ll x, y, g;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<Dot> dots(n);
    ll g_sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> dots[i].x >> dots[i].y >> dots[i].g;
        g_sum += dots[i].g;
    }

    ll ans = INT64_MAX;
    for (int i = 0; i < n; i++) {
        vector<pair<double, ll>> angles;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                double angle = atan2(dots[j].y - dots[i].y, dots[j].x - dots[i].x);
                angles.emplace_back(angle, dots[j].g);
            }
        }
        sort(angles.begin(), angles.end());
        ll l_sum = 0, r_sum = 0;
        deque<pair<double, ll>> l, r;
        for (int j = 1; j < angles.size(); j++) {
            double angle_diff = angles[j].first - angles[0].first;
            angle_diff = fmod(angle_diff + 2 * M_PI, 2 * M_PI);
            if (angle_diff < M_PI) {
                l_sum += angles[j].second;
                l.push_back(angles[j]);
            } else {
                r_sum += angles[j].second;
                r.push_back(angles[j]);
            }
        }
        ans = min(ans, abs(l_sum - r_sum));
        for (int j = 1; j < angles.size(); j++) {
            // add (j-1)-th angle to back of r
            r.push_back(angles[j - 1]);
            r_sum += angles[j - 1].second;

            // remove j-th angle from front of l or r
            if (!l.empty()) {
                l_sum -= l.front().second;
                l.pop_front();
            } else {
                r_sum -= r.front().second;
                r.pop_front();
            }

            // move some front angle from r to l
            while (!r.empty() && fmod(r.front().first - angles[j].first + 2 * M_PI, 2 * M_PI) < M_PI) {
                l.push_back(r.front());
                l_sum += r.front().second;
                r_sum -= r.front().second;
                r.pop_front();
            }

            // move some front angle from l to r
            while (!l.empty() && fmod(l.front().first - angles[j].first + 2 * M_PI, 2 * M_PI) >= M_PI) {
                r.push_back(l.front());
                r_sum += l.front().second;
                l_sum -= l.front().second;
                l.pop_front();
            }

            ans = min(ans, abs(l_sum - r_sum));
        }
    }

    cout << ans << '\n';

    return 0;
}