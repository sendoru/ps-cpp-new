#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
constexpr ll MOD = 1000000007;

// dp[i][0] := ���� i�� ��Ʈ�� �ϴ� ����Ʈ������ i�� �������̳� �������� �ϴ� ����� ����ġ�� ��
// dp[i][1] := ���� i�� ��Ʈ�� �ϴ� ����Ʈ������ i�� �������̳� �������� ���� �ʴ� ����� ����ġ�� ��
pair<ll, ll> solve(vector<vector<pair<ll, ll>>>& tree, vector<pair<ll, ll>>& dp, vector<bool>& visited, ll curNode)
{
	visited[curNode] = true;
	pair<ll, ll>& ret = dp[curNode];
	if (ret.first != -1) return ret;
	if (curNode != 1 && tree[curNode].size() == 1) return ret = { 0, 0 };
	ret = { 0, 0 };
	ll squareofSum = 0, sumofSquare = 0;
	for (auto next : tree[curNode])
	{
		ll nextNode = next.first, edgeCost = next.second;
		if (!visited[nextNode])
		{
			solve(tree, dp, visited, nextNode);
			ret.first += edgeCost * (dp[nextNode].first + 1);
			ret.second += dp[nextNode].first + dp[nextNode].second;
			ret.second %= MOD;
			ret.first %= MOD;
			squareofSum += edgeCost * (dp[nextNode].first + 1);
			squareofSum %= MOD;
			sumofSquare += ((edgeCost * (dp[nextNode].first + 1)) % MOD) * ((edgeCost * (dp[nextNode].first + 1)) % MOD);
			sumofSquare %= MOD;
		}
	}
	squareofSum *= squareofSum;
	squareofSum %= MOD;
	squareofSum += MOD;
	// 500000004 = 2^(-1) MOD 1000000007
	ret.second += ((squareofSum - sumofSquare) * 500000004) % MOD;
	ret.second %= MOD;
	return ret;
}

int main(void)
{
	int n;
	cin >> n;
	vector<vector<pair<ll, ll>>> tree(n + 1);
	vector<pair<ll, ll>> dp(n + 1, { -1, -1 });
	vector<bool> visited(n + 1);
	for (int i = 0; i < n - 1; i++)
	{
		ll s, e, w;
		cin >> s >> e >> w;
		tree[s].push_back({ e, w });
		tree[e].push_back({ s, w });
	}
	solve(tree, dp, visited, 1);
	cout << (dp[1].first + dp[1].second) % MOD << '\n';
	return 0;
}