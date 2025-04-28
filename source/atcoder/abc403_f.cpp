// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<string> dp(20200);

string solve(int n) {
    if (dp[n] != "") {
        return dp[n];
    }
    string n_str = to_string(n);
    string comp = "";
    for (int i = 0; i < n_str.size(); i++) {
        comp += "1";
    }
    if (n_str == comp) {
        return n_str;
    }

    int min_len = INT_MAX;
    string res = "";
    // sum
    for (int i = 1; i <= n - 1; i++) {
        string i_str = solve(i);
        string remain_str = solve(n - i);
        if (i_str.size() + remain_str.size() < min_len) {
            min_len = i_str.size() + remain_str.size();
            res = i_str + "+" + remain_str;
        }
    }

    // prod
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            string i_str = solve(i);
            string remain_str = solve(n / i);
            // check if plus sign is outside the parenthesis
            // i_str
            bool i_plus = false;
            int par_cnt = 0;
            for (int j = 0; j < i_str.size(); j++) {
                if (i_str[j] == '(') {
                    par_cnt++;
                }
                if (i_str[j] == ')') {
                    par_cnt--;
                }
                if (par_cnt == 0 && i_str[j] == '+') {
                    i_plus = true;
                    break;
                }
            }
            // remain_str
            bool remain_plus = false;
            par_cnt = 0;
            for (int j = 0; j < remain_str.size(); j++) {
                if (remain_str[j] == '(') {
                    par_cnt++;
                }
                if (remain_str[j] == ')') {
                    par_cnt--;
                }
                if (par_cnt == 0 && remain_str[j] == '+') {
                    remain_plus = true;
                    break;
                }
            }

            if (i_plus) {
                i_str = "(" + i_str + ")";
            }
            if (remain_plus) {
                remain_str = "(" + remain_str + ")";
            }
            if (i_str.size() + remain_str.size() < min_len) {
                min_len = i_str.size() + remain_str.size();
                res = i_str + "*" + remain_str;
            }
        }
    }

    return dp[n] = res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    cout << solve(n) << endl;

    return 0;
}