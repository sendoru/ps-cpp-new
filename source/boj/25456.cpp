// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;
typedef complex<double> cpx;

void fft(vector<cpx> &v, bool rev = false) {
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

// a *= b
void convolve(vector<cpx> &a, vector<cpx> &b) {
    int n = 1;
    while (n < a.size() + b.size()) {
        n <<= 1;
    }

    a.resize(n);
    b.resize(n);

    fft(a);
    fft(b);

    for (int i = 0; i < n; i++) {
        a[i] *= b[i];
    }

    fft(a, true);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s, t;
    cin >> s >> t;
    reverse(t.begin(), t.end());
    t += t;
    vector<cpx> a(s.size()), b(t.size());
    for (int i = 0; i < s.size(); i++) {
        a[i] = s[i] - '0';
    }
    for (int i = 0; i < t.size(); i++) {
        b[i] = t[i] - '0';
    }

    convolve(a, b);

    int ans = 0;
    for (int i = 0; i < a.size(); i++) {
        ans = max(ans, (int)(round(a[i].real())));
    }

    cout << ans << '\n';

    return 0;
}