// #include "atcoder/all"
#include <bits/stdc++.h>
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<string, ll> psl;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

pll add(const pll &a, const pll &b) {
    return {a.fi + b.fi, a.se + b.se};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    pll t_pos, a_pos;
    cin >> t_pos.fi >> t_pos.se;
    cin >> a_pos.fi >> a_pos.se;

    map<string, pll> dir_map = {
        {"U", {-1, 0}},
        {"D", {1, 0}},
        {"L", {0, -1}},
        {"R", {0, 1}},
    };
    ll n, m, l;
    cin >> n >> m >> l;

    vector<pair<pll, ll>> t_moves(m), a_moves(l);
    for (int i = 0; i < m; i++) {
        string dir;
        cin >> dir >> t_moves[i].se;
        t_moves[i].fi = dir_map[dir];
    }
    for (int i = 0; i < l; i++) {
        string dir;
        cin >> dir >> a_moves[i].se;
        a_moves[i].fi = dir_map[dir];
    }

    ll ans = 0;
    ll cur_time = 0;
    ll t_idx = 0, a_idx = 0;
    vector<ll> t_times_sum, a_times_sum;
    t_times_sum.push_back(t_moves[0].second);
    a_times_sum.push_back(a_moves[0].second);
    for (int i = 1; i < m; i++) {
        t_times_sum.push_back(t_times_sum.back() + t_moves[i].second);
    }
    for (int i = 1; i < l; i++) {
        a_times_sum.push_back(a_times_sum.back() + a_moves[i].second);
    }

    while (t_idx != m && a_idx != l) {
        ll t_time_eps = t_times_sum[t_idx] - cur_time;
        ll a_time_eps = a_times_sum[a_idx] - cur_time;
        ll time_eps = min(t_time_eps, a_time_eps);

        // 현재 위치가 같고, 이동 방향이 같으면
        if (t_pos == a_pos) {
            if (t_moves[t_idx].fi == a_moves[a_idx].fi) {
                ans += time_eps;
            }
        }

        else {
            // 현재 위치가 다르고, 반대 방향으로 이동하고, 이동 방향 축의 좌표가 같은 경우
            if (add(t_moves[t_idx].fi, a_moves[a_idx].fi) == pll{0, 0}) {
                // 이동 방향 축의 좌표가 같은지 확인
                int axis = (t_moves[t_idx].fi.fi == 0) ? 0 : 1;
                if ((axis == 0 && t_pos.fi == a_pos.fi) || (axis == 1 && t_pos.se == a_pos.se)) {
                    // 만나는 좌표까지 걸리는 시간 + 가까워지는 방향으로 이동하는지 확인
                    ll dist = a_moves[a_idx].fi.fi * (t_pos.fi - a_pos.fi) + a_moves[a_idx].fi.se * (t_pos.se - a_pos.se);
                    if (dist >= 0 && dist / 2 <= time_eps && dist % 2 == 0) {
                        ans++;
                    }
                }
            }
            // 현재 위치가 다르고, 수직 방향으로 이동하는 경우
            else {
                auto dir_sum = add(t_moves[t_idx].fi, a_moves[a_idx].fi);
                if (abs(dir_sum.fi) == 1 && abs(dir_sum.se) == 1) {
                    // 궤적이 만나는 좌표 계산
                    pll meet_pos;
                    // t의 x좌표가 불변
                    if (t_moves[t_idx].fi.fi == 0) {
                        meet_pos = {t_pos.fi, a_pos.se};
                    }
                    // t의 y좌표가 불변
                    else {
                        meet_pos = {a_pos.fi, t_pos.se};
                    }
                    // 만나는 좌표까지 걸리는 시간 확인
                    ll t_meet_time = t_moves[t_idx].fi.fi * (meet_pos.fi - t_pos.fi) + t_moves[t_idx].fi.se * (meet_pos.se - t_pos.se);
                    ll a_meet_time = a_moves[a_idx].fi.fi * (meet_pos.fi - a_pos.fi) + a_moves[a_idx].fi.se * (meet_pos.se - a_pos.se);
                    // 조건: 양수, 같음, time_eps 이하
                    if (t_meet_time > 0 && t_meet_time == a_meet_time && t_meet_time <= time_eps) {
                        ans++;
                    }
                }
            }
        }
        // 위치 갱신
        t_pos = add(t_pos, pll{t_moves[t_idx].fi.fi * time_eps, t_moves[t_idx].fi.se * time_eps});
        a_pos = add(a_pos, pll{a_moves[a_idx].fi.fi * time_eps, a_moves[a_idx].fi.se * time_eps});
        cur_time += time_eps;

        if (cur_time == t_times_sum[t_idx]) {
            t_idx++;
        }
        if (cur_time == a_times_sum[a_idx]) {
            a_idx++;
        }
    }

    cout << ans << "\n";

    return 0;
}