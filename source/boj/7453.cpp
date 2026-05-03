// #pragma GCC optimize("Ofast")

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

int main(void) {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    vector<int> A(n), B(n), C(n), D(n);

    for (int i = 0; i < n; i++) {
        cin >> A[i] >> B[i] >> C[i] >> D[i];
    }

    vector<int> arr1, arr2;
    arr1.reserve(n * n);
    arr2.reserve(n * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            arr1.push_back(A[i] + B[j]);
            arr2.push_back(C[i] + D[j]);
        }
    }

    sort(arr1.begin(), arr1.end(), greater<int>());
    sort(arr2.begin(), arr2.end());

    ll ans = 0;
    auto lo = arr2.begin(), up = arr2.begin();
    for (int i = 0; i < arr1.size(); i++) {
        int n = arr1[i];
        // int cnt = upper_bound(arr2.begin(), arr2.end(), -n) - lower_bound(arr2.begin(), arr2.end(), -n);
        // ans += cnt;
        while (lo != arr2.end() && *lo < -n) {
            lo++;
        }
        while (up != arr2.end() && *up <= -n) {
            up++;
        }
        ans += up - lo;
    }

    cout << ans << '\n';
    return 0;
}