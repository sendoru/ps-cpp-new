#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
* dp[r][state] := r��° �࿡ �ɾ��ִ� ����� ���¸� ��Ʈ����ŷ�� �� state�϶�, r + 1��°���� ������ ����� ���� �� �ִ� ����� �ִ�
*/
int solve(vector<int>& broken, vector<vector<int>>& dp, int r, int state)
{
	if (r == dp.size() - 1)
	{
		return 0;
	}
	int& ret = dp[r][state];
	if (ret != -1)
	{
		return ret;
	}
	// ���� �࿡�� �� �ɴ�, �׷��ϱ� ������ �����ϰų� ���ڰ� �μ��� �ڸ�
	int banned = (state >> 1) | (state << 1) | broken[r + 1];
	for (int nextState = 0; nextState < dp[0].size(); nextState++)
	{
		if (nextState & banned) continue;
		int bitCnt = 0;
		bool impossible = false;
		for (int i = 0; i < 10; i++)
		{
			if (nextState & (1 << i))
			{
				bitCnt++;
			}
			if ((nextState & (1 << (i + 1))) && (nextState & (1 << i)))
			{
				impossible = true;
				break;
			}
			if (impossible) continue;
		}
		ret = max(ret, bitCnt + solve(broken, dp, r + 1, nextState));
	}
	return ret;

}

int main(void)
{
	int t;
	cin >> t;
	while (t--)
	{
		int n, m;
		cin >> n >> m;
		vector<string> classroom(n + 1);
		for (int i = 0; i < m; i++)
		{
			classroom[0] += '.';
		}
		for (int i = 1; i <= n; i++)
		{
			cin >> classroom[i];
		}
		vector<int> broken(n + 1);
		for (int i = 0; i < classroom.size(); i++)
		{
			for (int j = 0; j < classroom[i].size(); j++)
			{
				if (classroom[i][j] == 'x')
				{
					broken[i] |= 1 << j;
				}
			}
		}
		vector<vector<int>> dp(n + 1, vector<int>(1ll << m, -1));
		cout << solve(broken, dp, 0, 0) << '\n';
	}
	return 0;
}