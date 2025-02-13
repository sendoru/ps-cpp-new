// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

const string A = "Fennec";
const string B = "Snuke";

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (n == 1) {
        cout << A << endl;
        return 0;
    } else if (n == 2) {
        cout << B << endl;
        return 0;
    }

    ll sum_a_mod2 = 0;
    for (int i = 0; i < n; i++) {
        sum_a_mod2 += a[i] % 2;
    }

    if (n % 2 == 0) {
        // a에서 n - 2개 번갈아가면서 선택
        // 선택한 수 합이 짝수면 Snuke, 홀수면 Fennec

        // sum(a[i]) % 2 == 0일 때,
        // a에서 홀수가 2o'개, 짝수가 n - 2o'개
        // Snuke는 Fennec이 선택한 것과 parity가 같은 것만 선택해서 이길 수 있음
        if (sum_a_mod2 % 2 == 0) {
            cout << B << endl;
        }
        // sum(a[i]) % 2 == 1일 때,
        // a에서 홀수가 2o' + 1개, 짝수가 n - 2o' - 1개
        else {
            int even_cnt = n - sum_a_mod2;
            if (even_cnt <= n / 2 - 1 && sum_a_mod2 <= n / 2 - 1) {
                cout << A << endl;
            } else {
                cout << B << endl;
            }
        }
    } else {
        // sum(a[i]) % 2 == 0일 때,
        // a에서 홀수가 2o'개, 짝수가 n - 2o'개
        // Fennec은 맨 처음 짝수를 내고 이후에는 Snuke가 선택한 것과 parity가 같은 것만 선택해서 이길 수 있음
        if (sum_a_mod2 % 2 == 0) {
            cout << A << endl;
        }
        // sum(a[i]) % 2 == 1일 때,
        // a에서 홀수가 2o' + 1개, 짝수가 n - 2o' - 1개
        else {
            cout << A << endl;
        }
    }

    return 0;
}