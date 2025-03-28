// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

ld solve(ld a, ld b, int k) {
    ld h = sqrt(a * a + b * b);
    ld r0 = (a + b - h) / 2;
    vector<ld> lengths = {r0};
    ld alpha = sqrt((1 - (a / h)) / 2);
    ld beta = sqrt((1 - (b / h)) / 2);
    ld ratio_1 = (1 - alpha) / (1 + alpha);
    ld ratio_2 = (1 - beta) / (1 + beta);
    ld ratio_3 = (sqrt(2) - 1) / (sqrt(2) + 1);

    for (int i = 0; i < 111; i++) {
        lengths.push_back(r0 * pow(ratio_1, i + 1));
        lengths.push_back(r0 * pow(ratio_2, i + 1));
        lengths.push_back(r0 * pow(ratio_3, i + 1));
    }

    sort(lengths.begin(), lengths.end(), greater<ld>());
    return lengths[k - 1] * lengths[k - 1] * M_PI;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(12);

    int n;
    cin >> n;
    while (n--) {
        ld a, b;
        int k;
        cin >> a >> b >> k;

        cout << solve(a, b, k) << '\n';
    }

    return 0;
}