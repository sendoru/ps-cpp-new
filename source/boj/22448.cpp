// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353; 
const ll MOD1 = (ll)1e9 + 7;

vector<string> parse(const string& s) {
    vector<string> res;
    int n = s.size();
    string token;
    string num = "0123456789";
    for (int i = 0; i < n; i++) {
        if (num.find(s[i]) != string::npos) {
            token += s[i];
        } else {
            if (!token.empty()) {
                res.push_back(token);
                token.clear();
            }
            res.push_back(string(1, s[i]));
        }
    }
    if (!token.empty()) {
        res.push_back(token);
    }
    return res;
}

ll solve_sub(vector<string>& tokens, map<char, int>& op_priority) {
    stack<ll> nums;
    stack<char> ops;

    auto apply_op = [&](char op, ll a, ll b) -> ll {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            default: return 0;
        }
    };


    for (const string& token : tokens) {
        // number
        if (isdigit(token[0])) {
            nums.push(stoll(token));
            continue;
        }

        char op = token[0];

        // bracket
        if (op == '(') {
            ops.push(op);
            continue;
        }
        if (op == ')') {
            while (!ops.empty() && ops.top() != '(') {
                char top_op = ops.top(); ops.pop();
                ll b = nums.top(); nums.pop();
                ll a = nums.top(); nums.pop();
                nums.push(apply_op(top_op, a, b));
            }
            ops.pop();
        }
        
        // op
        else {
            while (!ops.empty() && ops.top() != '(' &&
                   op_priority[ops.top()] >= op_priority[op]) {
                char top_op = ops.top(); ops.pop();
                ll b = nums.top(); nums.pop();
                ll a = nums.top(); nums.pop();
                nums.push(apply_op(top_op, a, b));
            }
            ops.push(op);
        }
    }
    while (!ops.empty()) {
        char top_op = ops.top(); ops.pop();
        ll b = nums.top(); nums.pop();
        ll a = nums.top(); nums.pop();
        nums.push(apply_op(top_op, a, b));
    }
    return nums.top();
}

ll solve(const string& s) {
    vector<string> tokens = parse(s);
    ll ans = INT64_MIN;
    for (int mask = 0; mask < 3 * 3 * 3; mask++) {
        map<char, int> op_priority;
        op_priority['+'] = mask / 9;
        op_priority['-'] = (mask / 3) % 3;
        op_priority['*'] = mask % 3;

        ll res = solve_sub(tokens, op_priority);
        ans = max(ans, res);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s;
    cin >> s;
    cout << solve(s) << "\n";

    return 0;
}