#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
constexpr ll MOD = 998244353, MAX = 300003;

// a: ó�� �־����� ����
// tree: ���׸�Ʈ Ʈ��
// node: ���׸�Ʈ Ʈ���� ��� ��ȣ
// start, end: ���׸�Ʈ Ʈ���� ����ϴ� ���� ������ start ~ end
ll init(vector<ll>& a, vector<ll>& tree, int node, int start, int end) {
	// node�� ���� ����� ���
	if (start == end) return tree[node] = a[start];

	else return tree[node] = (init(a, tree, node * 2, start, (start + end) / 2) + init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end)) % MOD;
}

// left, right: ���� ���ϴ� ������ left ~ right
// ������ ���������� init�� �Ȱ���
ll sum(vector<ll>& tree, int node, int start, int end, int left, int right) {
	// ���� [start, end]�� [left, right]�� ��ġ�� ���� ���
	if (left > end || right < start) return 0;
	// ���� [left, right]�� ���� [start, end]�� ������ ������ ���
	if (left <= start && right >= end) return tree[node];
	return (sum(tree, node * 2, start, (start + end) / 2, left, right) + sum(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right)) % MOD;
}

// diff: (������Ʈ�Ϸ��� ��) - (���� ��)
void update(vector<ll>& tree, int node, int start, int end, int index, ll diff) {
	if (index < start || index > end) return;

	if (start != end) {
		update(tree, node * 2, start, (start + end) / 2, index, diff);
		update(tree, node * 2 + 1, (start + end) / 2 + 1, end, index, diff);
	}
	tree[node] += diff;
	tree[node] % MOD;
}


ll modPow(ll base, ll exp)
{
	ll ret = 1;
	while (exp > 0)
	{
		if (exp % 2 == 1)
		{
			ret *= base;
			ret %= MOD;
		}
		base *= base;
		base %= MOD;
		exp /= 2;
	}
	return ret;
}

int main(void)
{
	int n;
	cin >> n;
	vector<ll> pows(MAX), invs(MAX);
	pows[0] = 1, invs[0] = 1, invs[1] = modPow(2, MOD - 2);
	for (int i = 1; i < MAX; i++)
	{
		pows[i] = (pows[i - 1] * 2) % MOD;
		invs[i] = (invs[i - 1] * invs[1]) % MOD;
	}

	vector<pair<ll, ll>> a(n);
	vector<pair<ll, ll>> compressed(n);
	for (int i = 0; i < n; i++)
	{
		cin >> a[i].first;
		a[i].second = i;
		compressed[i].first = a[i].first;
		compressed[i].second = i;
	}
	sort(a.begin(), a.end());
	sort(compressed.begin(), compressed.end());
	compressed[0].first = 0;
	for (int i = 1; i < compressed.size(); i++)
	{
		if (a[i].first == a[i - 1].first) compressed[i].first = compressed[i - 1].first;
		else compressed[i].first = compressed[i - 1].first + 1;
	}
	sort(compressed.begin(), compressed.end(), [](pair<ll, ll> a, pair<ll, ll> b) { return a.second < b.second; });

	vector<ll> segTree(1ll << ((ll)(ceil(log2l(compressed.size())) + 1)));
	ll ans = 0;
	for (int i = 0; i < compressed.size(); i++)
	{
		ans += sum(segTree, 1, 0, compressed.size() - 1, 0, compressed[i].first) * pows[i];
		ans %= MOD;
		update(segTree, 1, 0, compressed.size() - 1, compressed[i].first, invs[i + 1]);
	}
	cout << ans;
	return 0;
}