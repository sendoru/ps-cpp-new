#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const ll MOD9 = 998244353;
const ll MOD1 = (ll)1e9 + 7;

set<vector<short>> euler_tours;
struct Quadtree;
vector<Quadtree*> ptrs;

struct Quadtree {
    short val;
    Quadtree *child[4];
    // if same pattern exists, use reference
    Quadtree *ref;

    Quadtree(short val) : val(val) {
        for(int i = 0; i < 4; i++) {
            child[i] = nullptr;
        }
        ref = nullptr;
    }

    Quadtree(vector<vector<bool>>& v) {
        init(v);
    }

    bool operator==(const Quadtree &rhs) {
        if(val != rhs.val) {
            return false;
        }

        for(int i = 0; i < 4; i++) {
            if(child[i] == nullptr && rhs.child[i] == nullptr) {
                continue;
            }
            if(child[i] == nullptr || rhs.child[i] == nullptr) {
                return false;
            }
            if(*child[i] != *rhs.child[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Quadtree &rhs) {
        return !(*this == rhs);
    }

    void init(vector<vector<bool>>& v) {
        init(v, 0, 0, v.size());
    }
    void init(vector<vector<bool>>& v, int r, int c, int size) {
        val = -1;
        if(size == 1) {
            val = v[r][c];
            return;
        }

        int half = size / 2;
        for(int i = 0; i < 4; i++) {
            child[i] = new Quadtree(-1);
        }
        child[0]->init(v, r, c, half);
        child[1]->init(v, r, c + half, half);
        child[2]->init(v, r + half, c, half);
        child[3]->init(v, r + half, c + half, half);

        if(child[0]->val != -1 && child[0]->val == child[1]->val && child[1]->val == child[2]->val && child[2]->val == child[3]->val) {
            val = child[0]->val;
            for(int i = 0; i < 4; i++) {
                delete child[i];
                child[i] = nullptr;
            }
        }
    }


    // each pattern can be identified by euler tour
    vector<short> get_euler_tour() {
        vector<short> ret;
        get_euler_tour(ret);
        return ret;
    }

    vector<short> get_euler_tour(vector<short>& ret) {
        ret.push_back(val);
        for(int i = 0; i < 4; i++) {
            if(child[i] != nullptr) {
                child[i]->get_euler_tour(ret);
            }
        }
        ret.push_back(val);
        return ret;
    }



    int get_node_cnt() {
        if(val != -1) {
            return 1;
        }

        int ret = 1;
        for(int i = 0; i < 4; i++) {
            if(child[i] != nullptr) {
                ret += child[i]->get_node_cnt();
            }
        }
        return ret;
    }

    int get_node_cnt_with_compress() {
        if(val != -1) {
            return 1;
        }

        int ret = 1;
        for(int i = 0; i < 4; i++) {
            if(child[i] != nullptr) {
                ret += child[i]->get_node_cnt_with_compress();
            }
        }

        for(auto it = ptrs.begin(); it != ptrs.end(); it++) {
            if(*this == **it) {
                // ref = *it;
                return 0;
            }
        }
        ptrs.push_back(this);
        return ret;
    }
};

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int n_adj = 1;
    while(n_adj < n || n_adj < m) {
        n_adj <<= 1;
    }

    vector<vector<bool>> v(n_adj, vector<bool>(n_adj, 0));
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for(int j = 0; j < s.length(); j++) {
            v[i][j] = s[j] - '0';
        }
    }

    Quadtree qt(v);

    cout << qt.get_node_cnt() << ' ' << qt.get_node_cnt_with_compress() << '\n';


    return 0;
}

/*
10111011
01110111
10101010
01110111
10111011
01110111
10101010
01110111
*/