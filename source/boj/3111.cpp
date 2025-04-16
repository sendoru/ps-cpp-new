#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool check_front(deque<char> &s, string &w) {
    if (s.size() < w.size())
        return false;
    for (int i = 0; i < w.size(); i++)
        if (s[i] != w[i])
            return false;

    return true;
}

bool check_back(deque<char> &s, string &w) {
    if (s.size() < w.size())
        return false;
    int offset = s.size() - w.size();
    for (int i = 0; i < w.size(); i++)
        if (s[offset + i] != w[i])
            return false;

    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string w, s;
    cin >> w;
    cin >> s;
    deque<char> l, m, r;
    for (auto elem : s)
        m.push_back(elem);

    int cnt = 0;
    while (true) {
        bool done = false;

        while (!check_back(l, w)) {
            if (!m.empty()) {
                l.push_back(m.front());
                m.pop_front();
            } else if (!r.empty()) {
                l.push_back(r.front());
                r.pop_front();
            } else {
                done = true;
                break;
            }
        }
        if (!done) {
            for (int i = 0; i < w.size(); i++) {
                l.pop_back();
            }
        }
        if (done) {
            break;
        }

        while (!check_front(r, w)) {
            if (!m.empty()) {
                r.push_front(m.back());
                m.pop_back();
            } else if (!l.empty()) {
                r.push_front(l.back());
                l.pop_back();
            } else {
                done = true;
                break;
            }
        }
        if (!done) {
            for (int i = 0; i < w.size(); i++) {
                r.pop_front();
            }
        }
        if (done) {
            break;
        }
    }

    for (auto &elem : l)
        cout << elem;
    for (auto &elem : m)
        cout << elem;
    for (auto &elem : r)
        cout << elem;

    return 0;
}