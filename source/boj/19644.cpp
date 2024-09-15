// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll l;
    cin >> l;
    ll range, damage;
    cin >> range >> damage;

    ll cnt;
    cin >> cnt;
    vector<ll> hp(l + 1);
    for (int i = 1; i <= l; i++) {
        cin >> hp[i];
        hp[i] -= min(range * damage, i * damage);
    }
    // 이제 hp에는 모든 턴에 기관총을 갈겼을 때 영거리에서의 남은 hp가 있음

    deque<ll> dq(range - 1, 0);
    ll damage_reduced = 0;
    for (int i = 1; i <= l; i++) {
        hp[i] += damage_reduced;
        if (hp[i] > 0) {
            damage_reduced += damage;
            dq.push_back(1);
            if (cnt == 0) {
                cout << "NO";
                return 0;
            } else {
                cnt--;
            }
        } else {
            dq.push_back(0);
        }
        damage_reduced -= damage * dq.front();
        dq.pop_front();
    }

    cout << "YES";
    return 0;
}