// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef complex<double> cpx;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

void inplace_fft(vector<cpx> &v, bool rev = false) {
    int n = v.size();

    if (n == 1) {
        return;
    }

    int log2 = 1;
    while ((1 << log2) < n) {
        log2++;
    }
    v.resize(1 << log2);

    // bit reverse
    for (int i = 0; i < (1 << log2); i++) {
        int j = 0;
        for (int k = 0; k < log2; k++) {
            if (i & (1 << k)) {
                j |= (1 << (log2 - 1 - k));
            }
        }
        if (i < j) {
            swap(v[i], v[j]);
        }
    }

    for (int sz = 2; sz <= (1 << log2); sz <<= 1) {
        double ang = 2 * M_PI / sz;
        if (rev) {
            ang = -ang;
        }
        cpx w = cpx(cos(ang), sin(ang));
        for (int i = 0; i < n; i += sz) {
            cpx wp = 1;
            for (int j = 0; j < sz / 2; j++) {
                cpx left = v[i + j];
                cpx right = v[i + j + sz / 2] * wp;
                v[i + j] = left + right;
                v[i + j + sz / 2] = left - right;
                wp *= w;
            }
        }
    }

    if (rev) {
        for (int i = 0; i < n; i++) {
            v[i] /= n;
        }
    }
}

vector<double> self_convolve(vector<double> &a) {
    int n = 1;
    while (n < 2 * a.size()) {
        n <<= 1;
    }

    a.resize(n);

    vector<cpx> fa(a.begin(), a.end());
    inplace_fft(fa);

    for (int i = 0; i < n; i++) {
        fa[i] *= fa[i];
    }

    inplace_fft(fa, true);

    vector<double> ret(n);
    for (int i = 0; i < n; i++) {
        ret[i] = fa[i].real();
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<double> a(n);
    for (ll i = 1; i < n; i++) {
        a[i * i % n] += 1;
    }

    a.resize(2 * n);
    vector<double> b = self_convolve(a);
    ll ans = 0;
    for (int i = 0; i < 2 * n; i++) {
        ans += (ll)round(b[i]) * (ll)round(a[i % n]);
    }

    ll same_cnt = 0;
    for (ll i = 1; i < n; i++) {
        same_cnt += (ll)round(a[2 * i * i % n]);
    }
    ans = (ans - same_cnt) / 2 + same_cnt;
    cout << ans << '\n';

    return 0;
}