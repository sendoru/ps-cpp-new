#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <set>
#include <string>
#include <algorithm>
typedef long long ll;
constexpr int INF = 0x3fffffff;
using namespace std;

// a: ó�� �־����� ����
// tree: ���׸�Ʈ Ʈ��
// node: ���׸�Ʈ Ʈ���� ��� ��ȣ
// start, end: ���׸�Ʈ Ʈ���� ����ϴ� ���� ������ start ~ end
int min(int a, int b)
{
    return a < b ? a : b;
}

pair<int, int> min(pair<int, int> a, pair<int, int> b)
{
    if (a.first < b.first)
    {
        return a;
    }
    if (a.first > b.first)
    {
        return b;
    }
    if (a.second < b.second)
    {
        return a;
    }
    return b;
}

pair<int, int> init(vector<pair<int, int> >& a, vector<pair<int, int> >& tree, int node, int start, int end)
{
    // node�� ���� ����� ���
    if (start == end)
    {
        return tree[node] = a[start];
    }
    else
    {
        return tree[node] = min(init(a, tree, node * 2, start, (start + end) / 2), init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end));
    }
}

// left, right: �ּڰ��� ���ϴ� ������ left ~ right
// ������ ���ڴ� init�� �Ȱ���
pair<int, int> min(vector<pair<int, int> >& tree, int node, int start, int end, int left, int right)
{
    // ���� [start, end]�� [left, right]�� ��ġ�� ���� ���
    if (left > end || right < start)
    {
        return { INF, -1 };
    }
    // ���� [left, right]�� ���� [start, end]�� ������ ������ ���
    if (left <= start && right >= end)
    {
        return tree[node];
    }
    return min(min(tree, node * 2, start, (start + end) / 2, left, right), min(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right));
}

void update(vector<pair<int, int> >& tree, int index, pair<int, int> newValue)
{
    int node = tree.size() / 2 + index;
    tree[node] = newValue;
    node /= 2;
    while (node != 0)
    {
        tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
        node /= 2;
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= n; i++) b[i] += i;

    vector<vector<int>> ans(n + 1, vector<int>(5));
    for (int i = 1; i <= n; i++)
    {
        /*
        * ans[i][0] := ������ġ
        * ans[i][1] := �̲����� ���� ��ġ
        * ans[i][2] := �̲����� ���� ��ġ���� �ִ��� �����Ҽ� �ִ°Ÿ�
        * 
        */
        ans[i][0] = i;
        ans[i][1] = b[i];
        ans[i][2] = a[b[i]];
        ans[i][3] = INF;
        ans[i][4] = -1;
    }

    sort(ans.begin(), ans.end(), [](vector<int> aa, vector<int> bb) { return aa[1] < bb[1]; });

    int h = (int)ceil(log2(n + 1));
    int treeSize = 1 << (h + 1);
    vector<pair<int, int>> tree(treeSize);
    for (int i = 0; i < treeSize; i++)
    {
        tree[i].first = INF;
        tree[i].second = -1;
    }

    for (int i = 1; i <= n; i++)
    {
        if (ans[i][2] == ans[i][1])
        {
            ans[i][3] = 1;
            ans[i][4] = 0;
        }
        else
        {
            auto temp = min(tree, 1, 0, n, ans[i][1] - ans[i][2], ans[i][1]);
            ans[i][3] = temp.first + 1;
            ans[i][4] = temp.second;
        }
        update(tree, ans[i][0], make_pair(ans[i][3], ans[i][0]));
    }
    sort(ans.begin(), ans.end());
    vector<int> anss;
    vector<int>& ini = ans.back();
    anss.push_back(ini[4]);
    if (anss.back() == -1)
    {
        cout << -1;
        return 0;
    }
    while (anss.back() != 0)
    {
        ini = ans[anss.back()];
        anss.push_back(ini[4]);
    }



    cout << anss.size() << '\n';
    for (int elem : anss)
    {
        cout << elem << ' ';
    }

    return 0;
}