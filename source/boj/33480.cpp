// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const ll RANGE = 100;

ll dot(vector<ll> &a, vector<ll> &b)
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}

ll l2norm(vector<ll> &a)
{
    return a[0] * a[0] + a[1] * a[1] + a[2] * a[2] + a[3] * a[3];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<ll> dis(-100, 100);

    int n;
    cin >> n;
    vector<vector<ll>> dots(n, vector<ll>(4));
    for (int i = 0; i < n; i++) {
        cin >> dots[i][0] >> dots[i][1] >> dots[i][2] >> dots[i][3];
    }
    ll ans = 0;
    vector<ll> selected;
    for (int _ = 0; _ < 3e4; _++) {
        ll x1 = dis(gen);
        ll x2 = dis(gen);
        ll x3 = dis(gen);
        ll x4 = dis(gen);
        if (x1 == 0 && x2 == 0 && x3 == 0 && x4 == 0) {
            continue;
        }
        vector<ll> dir_vec = {x1, x2, x3, x4};
        ll cur_ans = 0;
        vector<ll> cur_selected;
        for (int i = 0; i < 10; i++) {
            vector<ll> cur_vec(4);
            vector<ll> cur_cur_selected;
            for (int j = 0; j < n; j++) {
                if (dot(dir_vec, dots[j]) > 0) {
                    cur_vec[0] += dots[j][0];
                    cur_vec[1] += dots[j][1];
                    cur_vec[2] += dots[j][2];
                    cur_vec[3] += dots[j][3];
                    cur_cur_selected.push_back(j);
                }
            }
            ll cur_l2norm = l2norm(cur_vec);
            if (cur_l2norm > cur_ans) {
                cur_ans = cur_l2norm;
                dir_vec = cur_vec;
                cur_selected = cur_cur_selected;
            }
        }
        if (cur_ans > ans) {
            ans = cur_ans;
            selected = cur_selected;
        }
    }

    cout << selected.size() << "\n";
    for (auto i : selected) {
        cout << i + 1 << " ";
    }

    return 0;
}