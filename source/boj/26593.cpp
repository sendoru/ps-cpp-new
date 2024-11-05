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

    vector<tuple<string, int, double>> v;
    while (true) {
        string s;
        int a;
        double b;
        cin >> s >> a >> b;
        if (!cin) {
            break;
        }
        b *= a;
        v.push_back({s, a, b});
    }

    sort(v.begin(), v.end(), [](auto a, auto b) -> bool {
        if (get<2>(a) != get<2>(b)) {
            return get<2>(a) > get<2>(b);
        }
        if (get<1>(a) != get<1>(b)) {
            return get<1>(a) > get<1>(b);
        }
        return get<0>(a) < get<0>(b);
    });

    cout << fixed << setprecision(2);
    for (auto [s, a, b] : v) {
        cout << '$' << b << " - " << s << '/' << a << '\n';
    }

    return 0;
}