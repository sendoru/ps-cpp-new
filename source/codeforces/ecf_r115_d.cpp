#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
typedef long long ll;
using namespace std;

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
		ll n;
		cin >> n;
		vector<pair<ll, ll>> problems(n);
		for (int i = 0; i < n; i++)
		{
			cin >> problems[i].first;
			cin >> problems[i].second;
		}

		vector<ll> topicCnt(n + 1);
		vector<vector<ll>>	diffCnt(n + 1);
		ll topicSquareSum = 0, diffSquareSum = 0;
		for (auto elem : problems)
		{
			topicCnt[elem.first]++;
			diffCnt[elem.second].push_back(elem.first);
		}

		ll ans = n * (n - 1) * (n - 2) / 6;

		for (int i = 0; i < diffCnt.size(); i++)
		{
			if (diffCnt[i].size() >= 2)
			{
				for (auto elem : diffCnt[i])
				{
					ans -= (diffCnt[i].size() - 1) * (topicCnt[elem] - 1);
				}
			}
		}

		cout << ans << '\n';
	}
	return 0;
}