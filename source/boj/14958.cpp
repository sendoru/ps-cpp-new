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

vector<cpx> fft(vector<cpx> &v, bool rev = false) {
    int n = v.size();

    if (n == 1) {
        return v;
    }

    int log2 = 1;
    while ((1 << log2) < n) {
        log2++;
    }

    vector<cpx> a(n);

    // bit reverse
    for (int i = 0; i < (1 << log2); i++) {
        int j = 0;
        for (int k = 0; k < log2; k++) {
            if (i & (1 << k)) {
                j |= (1 << (log2 - 1 - k));
            }
        }
        a[i] = v[j];
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
                cpx u = a[i + j];
                cpx v = a[i + j + sz / 2] * wp;
                a[i + j] = u + v;
                a[i + j + sz / 2] = u - v;
                wp *= w;
            }
        }
    }

    if (rev) {
        for (int i = 0; i < n; i++) {
            a[i] /= n;
        }
    }

    return a;
}

vector<double> convolve(vector<double> a, vector<double> b) {
    int n = 1;
    while (n < a.size() + b.size()) {
        n <<= 1;
    }

    a.resize(n);
    b.resize(n);

    vector<cpx> ca(a.begin(), a.end());
    vector<cpx> cb(b.begin(), b.end());
    vector<cpx> fa = fft(ca);
    vector<cpx> fb = fft(cb);

    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }

    fa = fft(fa, true);

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

    int n, m;
    cin >> n >> m;
    string s1, s2;
    cin >> s1 >> s2;
    reverse(s2.begin(), s2.end());

    vector<double> a(2 * n), b(2 * m);

    // 'R' on a and 'P' on b
    for (int i = 0; i < n; i++) {
        if (s1[i] == 'R')
            a[i] = 1;
    }
    for (int i = 0; i < m; i++) {
        if (s2[i] == 'P')
            b[i] = 1;
    }

    vector<double> ret1 = convolve(a, b);

    // 'S' on a and 'R' on b
    fill(a.begin(), a.end(), 0);
    fill(b.begin(), b.end(), 0);
    for (int i = 0; i < n; i++) {
        if (s1[i] == 'S')
            a[i] = 1;
    }
    for (int i = 0; i < m; i++) {
        if (s2[i] == 'R')
            b[i] = 1;
    }

    vector<double> ret2 = convolve(a, b);

    // 'P' on a and 'S' on b
    fill(a.begin(), a.end(), 0);
    fill(b.begin(), b.end(), 0);
    for (int i = 0; i < n; i++) {
        if (s1[i] == 'P')
            a[i] = 1;
    }
    for (int i = 0; i < m; i++) {
        if (s2[i] == 'S')
            b[i] = 1;
    }

    vector<double> ret3 = convolve(a, b);

    int ans = 0;
    for (int i = s2.length() - 1; i < ret1.size(); i++) {
        ans = max(ans, (int)round(ret1[i] + ret2[i] + ret3[i]));
    }
    cout << ans << '\n';

    return 0;
}