#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const ll MOD1 = 1e9 + 7;
const ll MOD9 = 998244353;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int T, test_case;
    /*
       The freopen function below opens input.txt file in read only mode, and
       afterward, the program will read from input.txt file instead of
       standard(keyboard) input. To test your program, you may save input data
       in input.txt file, and use freopen function to read from the file when
       using cin function. You may remove the comment symbols(//) in the below
       statement and use it. Use #include<cstdio> or #include <stdio.h> to use
       the function in your program. But before submission, you must remove the
       freopen function or rewrite comment symbols(//).
     */

    // freopen("input.txt", "r", stdin);

    cin >> T;
    for (test_case = 0; test_case < T; test_case++) {

        ll n;
        cin >> n;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        int q;
        cin >> q;
        vector<ll> ans;
        while (q--) {
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            priority_queue<ll, vector<ll>, greater<>> pq;
            for (int i = l; i <= r; i++) {
                if (a[i] != 1) {
                    pq.push(a[i]);
                }
            }
            ll cur_ans = 0;
            while (!pq.empty()) {
                ll cur_num = pq.top();
                ll pop_cnt = 0;
                while (!pq.empty() && pq.top() == cur_num && pop_cnt < cur_num) {
                    pq.pop();
                    pop_cnt++;
                }
                if (pop_cnt == cur_num) {
                    cur_ans++;
                    pq.push(cur_num * cur_num);
                }
            }
            ans.push_back(cur_ans);
        }

        cout << "Case #" << test_case + 1 << endl;
        for (auto elem : ans)
            cout << elem << endl;
    }

    return 0;
}