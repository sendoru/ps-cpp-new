#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pdd;
const ll INF = 1e16;

double getDistSum(vector<pdd> &v, pdd cur, int k) {
    vector<double> dists(v.size());
    for (int i = 0; i < v.size(); i++) {
        auto elem = v[i];
        dists[i] = sqrt((cur.first - elem.first) * (cur.first - elem.first) + (cur.second - elem.second) * (cur.second - elem.second));
    }
    sort(dists.begin(), dists.end(), greater<double>());
    double res = 0;
    for (int i = 0; i < k; i++) {
        res += dists[i];
    }
    return res;
}

pdd getGrad(vector<pdd> &v, pdd cur, int k) {
    double delta = 0.0001;
    double dx, dy;
    dx = (getDistSum(v, {cur.first + delta, cur.second}, k) - getDistSum(v, {cur.first - delta, cur.second}, k)) / (2 * delta);
    dy = (getDistSum(v, {cur.first, cur.second + delta}, k) - getDistSum(v, {cur.first, cur.second - delta}, k)) / (2 * delta);
    return {dx, dy};
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<pdd> v(n);
    pdd cur = {0, 0};
    for (auto &elem : v) {
        cin >> elem.first >> elem.second;
        cur.first += elem.first;
        cur.second += elem.second;
    }

    cur.first /= n;
    cur.second /= n;

    double minDist = getDistSum(v, cur, k);
    auto opt = cur;
    double rho = 5;
    for (int _ = 0; _ < 5000; _++) {
        auto grad = getGrad(v, cur, k);
        cur.first -= rho * grad.first;
        cur.second -= rho * grad.second;
        double curDist = getDistSum(v, cur, k);
        if (curDist < minDist) {
            minDist = curDist;
            opt = cur;
        }
        rho *= 0.999;
    }

    cout.precision(12);
    cout << minDist;
    return 0;
}