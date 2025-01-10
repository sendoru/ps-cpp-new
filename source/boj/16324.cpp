// #include "atcoder/all"
#include <bits/stdc++.h>
// #define DEBUG

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

string solve_inner(ll zero_cnt, ll one_cnt, ll b, ll c) {
    if (b + c != zero_cnt * one_cnt) {
        return "";
    }
    string ret;
    while (one_cnt + zero_cnt > 0) {
        while (b >= one_cnt && zero_cnt > 0) {
            ret += '0';
            b -= one_cnt;
            zero_cnt--;
        }
        while (c >= zero_cnt && one_cnt > 0) {
            ret += '1';
            c -= zero_cnt;
            one_cnt--;
        }
    }

    return ret;
}

string solve(ll a, ll b, ll c, ll d) {
    // solution of x(x - 1) = 2a
    // x^2 - x - 2a = 0
    // x = (1 + sqrt(1 + 8a)) / 2
    ll zero_cnt = round((1 + sqrtl(1 + 8 * a)) / 2);
    ll one_cnt = round((1 + sqrtl(1 + 8 * d)) / 2);
    if (zero_cnt * (zero_cnt - 1) != 2 * a || one_cnt * (one_cnt - 1) != 2 * d) {
        return "impossible";
    }
    string ans;
    if (a == 0 && d == 0) {
        ans = max(ans, solve_inner(0, 0, b, c));
        ans = max(ans, solve_inner(0, 1, b, c));
        ans = max(ans, solve_inner(1, 0, b, c));
        ans = max(ans, solve_inner(1, 1, b, c));
    } else if (a == 0 && d != 0) {
        ans = max(ans, solve_inner(0, one_cnt, b, c));
        ans = max(ans, solve_inner(1, one_cnt, b, c));
    } else if (a != 0 && d == 0) {
        ans = max(ans, solve_inner(zero_cnt, 0, b, c));
        ans = max(ans, solve_inner(zero_cnt, 1, b, c));
    } else {
        ans = max(ans, solve_inner(zero_cnt, one_cnt, b, c));
    }

    if (a + b + c + d != 0 && ans == "") {
        return "impossible";
    } else {
        return ans;
    }
}

bool check(string s, ll a, ll b, ll c, ll d) {
    for (int i = 0; i < s.length(); i++) {
        for (int j = i + 1; j < s.length(); j++) {
            if (s[i] == '0' && s[j] == '0') {
                a--;
            } else if (s[i] == '0' && s[j] == '1') {
                b--;
            } else if (s[i] == '1' && s[j] == '0') {
                c--;
            } else {
                d--;
            }
        }
    }
    return a == 0 && b == 0 && c == 0 && d == 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef DEBUG
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<ll> dis_100(0, 100), dis_1000(0, 1000);
    cout << "Full random test:" << endl;
    for (int i = 0; i < 100; i++) {
        ll a = dis_1000(gen);
        ll b = dis_1000(gen);
        ll c = dis_1000(gen);
        ll d = dis_1000(gen);
        string ans = solve(a, b, c, d);
        if (ans != "impossible") {
            if (!check(ans, a, b, c, d)) {
                cout << "Wrong answer\n";
                cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
                cout << ans << '\n';
                return 0;
            }
        }
    }
    cout << "Passed" << endl
         << endl;

    cout << "Edge test (solution always exists):" << endl;
    for (int i = 0; i < 100; i++) {
        ll zero_cnt = dis_100(gen);
        ll one_cnt = dis_100(gen);
        ll a = zero_cnt * (zero_cnt - 1) / 2;
        ll d = one_cnt * (one_cnt - 1) / 2;
        uniform_int_distribution<ll> dis(0, zero_cnt * one_cnt);
        ll b = dis(gen);
        ll c = zero_cnt * one_cnt - b;
        string ans = solve(a, b, c, d);
        if (ans == "impossible" || !check(ans, a, b, c, d)) {
            cout << "Wrong answer\n";
            cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
            cout << ans << '\n';
            return 0;
        }
    }
    cout << "Passed" << endl
         << endl;

    cout << "Edge test (solution always exists, a fixed to 0):" << endl;
    for (int i = 0; i < 100; i++) {
        ll zero_cnt = dis_100(gen) & 1;
        ll one_cnt = dis_100(gen);
        ll a = 0;
        ll d = one_cnt * (one_cnt - 1) / 2;
        uniform_int_distribution<ll> dis(0, zero_cnt * one_cnt);
        ll b = dis(gen);
        ll c = zero_cnt * one_cnt - b;
        string ans = solve(a, b, c, d);
        if (ans == "impossible" || !check(ans, a, b, c, d)) {
            cout << "Wrong answer\n";
            cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
            cout << ans << '\n';
            return 0;
        }
    }
    cout << "Passed" << endl
         << endl;

    cout << "Edge test (solution always exists, d fixed to 0):" << endl;
    for (int i = 0; i < 100; i++) {
        ll zero_cnt = dis_100(gen);
        ll one_cnt = dis_100(gen) & 1;
        ll a = zero_cnt * (zero_cnt - 1) / 2;
        ll d = one_cnt * (one_cnt - 1) / 2;
        uniform_int_distribution<ll> dis(0, zero_cnt * one_cnt);
        ll b = dis(gen);
        ll c = zero_cnt * one_cnt - b;
        string ans = solve(a, b, c, d);
        if (ans == "impossible" || !check(ans, a, b, c, d)) {
            cout << "Wrong answer\n";
            cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
            cout << ans << '\n';
            return 0;
        }
    }
    cout << "Passed" << endl
         << endl;

    cout << "Edge test (solution always exists, a and d fixed to 0):" << endl;
    for (int i = 0; i < 20; i++) {
        ll zero_cnt = dis_100(gen) & 1;
        ll one_cnt = dis_100(gen) & 1;
        ll a = zero_cnt * (zero_cnt - 1) / 2;
        ll d = one_cnt * (one_cnt - 1) / 2;
        uniform_int_distribution<ll> dis(0, zero_cnt * one_cnt);
        ll b = dis(gen);
        ll c = zero_cnt * one_cnt - b;
        string ans = solve(a, b, c, d);
        if (ans == "impossible" || !check(ans, a, b, c, d)) {
            cout << "Wrong answer\n";
            cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
            cout << ans << '\n';
            return 0;
        }
    }
    cout << "Passed" << endl
         << endl;

#else

    ll a, b, c, d;
    cin >> a >> b >> c >> d;

    cout << solve(a, b, c, d) << '\n';
#endif

    return 0;
}