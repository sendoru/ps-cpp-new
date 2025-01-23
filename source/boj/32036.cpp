// #include "atcoder/all"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

template <typename T>
struct MedianHeap {
    priority_queue<T> max_heap;
    priority_queue<T, vector<T>, greater<T>> min_heap;

    ll size = 0;
    // for each s[i], diff_sum += abs(s[i] - median)
    ll diff_sum = 0;

    void push(T val) {
        if (size == 0) {
            max_heap.push(val);
            size++;
            return;
        }
        ll pre_med = max_heap.top();
        if (max_heap.empty() || val <= max_heap.top()) {
            max_heap.push(val);
        } else {
            min_heap.push(val);
        }

        if (max_heap.size() > min_heap.size() + 1) {
            min_heap.push(max_heap.top());
            max_heap.pop();
        } else if (min_heap.size() > max_heap.size()) {
            max_heap.push(min_heap.top());
            min_heap.pop();
        }

        diff_sum += abs(max_heap.top() - val);

        if (max_heap.size() == min_heap.size()) {
            diff_sum += abs(max_heap.top() - pre_med);
        }

        size++;
    }

    T get_median() {
        // prioritize smaller value if the size of heaps are same
        return max_heap.top();
    }

    T get_diff_sum() { return diff_sum; }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll q, offset = 0;
    ;
    cin >> q;
    MedianHeap<ll> mh;

    while (q--) {
        ll t;
        cin >> t;
        if (t == 1) {
            ll x, y;
            cin >> x >> y;
            mh.push(x);
            offset += y;
        } else {
            cout << mh.get_median() << " " << mh.get_diff_sum() + offset << '\n';
        }
    }

    return 0;
}