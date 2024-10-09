// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

vector<pii> prev_seq;
vector<int> len;

// the length of the shortest bracket sequence
// that reprensent n
int solve(int n)
{
    if (n == 1) {
        return 0;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    prev_seq.resize(1'000'001);
    len.resize(1'000'001);
    fill(prev_seq.begin(), prev_seq.end(), make_pair(-1, -1));
    fill(len.begin(), len.end(), -1);

    return 0;
}