#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;
typedef long long ll;

// a: ó�� �־����� ����
// tree: ���׸�Ʈ Ʈ��
// node: ���׸�Ʈ Ʈ���� ��� ��ȣ
// start, end: ���׸�Ʈ Ʈ���� ����ϴ� ���� ������ start ~ end
ll init(vector<ll>& a, vector<ll>& tree, int node, int start, int end) {
	// node�� ���� ����� ���
	if (start == end) return tree[node] = a[start];

	else return tree[node] = init(a, tree, node * 2, start, (start + end) / 2) + init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
}

// left, right: ���� ���ϴ� ������ left ~ right
// ������ ���������� init�� �Ȱ���
ll sum(vector<ll>& tree, int node, int start, int end, int left, int right) {
	// ���� [start, end]�� [left, right]�� ��ġ�� ���� ���
	if (left > end || right < start) return 0;
	// ���� [left, right]�� ���� [start, end]�� ������ ������ ���
	if (left <= start && right >= end) return tree[node];
	return sum(tree, node * 2, start, (start + end) / 2, left, right) + sum(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
}

// diff: (������Ʈ�Ϸ��� ��) - (���� ��)
void update(vector<ll>& tree, int node, int start, int end, int index, ll diff) {
	if (index < start || index > end) return;

	tree[node] += diff;
	if (start != end) {
		update(tree, node * 2, start, (start + end) / 2, index, diff);
		update(tree, node * 2 + 1, (start + end) / 2 + 1, end, index, diff);
	}
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		vector<pair<ll, ll>> a(n), compressed(n);
		for (int i = 0; i < n; i++)
		{
			cin >> a[i].first;
			compressed[i].first = a[i].first;
			a[i].second = i;
			compressed[i].second = a[i].second;
		}
		sort(a.begin(), a.end());
		sort(compressed.begin(), compressed.end());
		compressed[0].first = 0;
		for (int i = 1; i < n; i++)
		{
			if (a[i].first == a[i - 1].first) compressed[i].first = compressed[i - 1].first;
			else compressed[i].first = compressed[i - 1].first + 1;
		}
		int maxVal = compressed.back().first;
		sort(compressed.begin(), compressed.end(), [](pair<ll, ll> a, pair<ll, ll> b) {return a.second < b.second; });

		vector<ll> aa(n);
		for (int i = 0; i < n; i++) aa[i] = compressed[i].first;
		a.clear(); compressed.clear();
		vector<ll> segTree(1ll << ((ll)ceil(log2l(maxVal + 4)) + 1));

		ll ans = 0;
		update(segTree, 1, 0, maxVal + 3, aa[0], 1);
		for (int i = 1; i < n; i++)
		{
			ll lower = sum(segTree, 1, 0, maxVal + 3, 0, aa[i] - 1);
			ll upper = sum(segTree, 1, 0, maxVal + 3, aa[i] + 1, maxVal + 3);
			ans += min(lower, upper);
			update(segTree, 1, 0, maxVal + 3, aa[i], 1);
		}

		cout << ans << '\n';
	}

	return 0;
}