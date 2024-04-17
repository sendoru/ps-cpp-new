#include <iostream>
#include <vector>
#define INF 987654321

using namespace std;
typedef long long ll;

int expand(int n, int w, vector<vector<int> >& nums)
{
	// dp[i][0] := i - 1��° �������� ���� Ŀ���ϰ� i��° ���� �Ʒ����� Ŀ���ϴ� �� �ʿ��� �ּ� Ư���δ� ��
	// dp[i][1] := i - 1��° �������� ���� Ŀ���ϰ� i��° ���� ������ Ŀ���ϴ� �� �ʿ��� �ּ� Ư���δ� ��
	// dp[i][2] := i��° ������ ���� Ŀ���ϴ� �� �ʿ��� �ּ� Ư���δ� ��
	vector<vector<int> > dp(n, vector<int>(3));

	dp[0][0] = 1;
	dp[0][1] = 1;
	if (nums[0][0] + nums[0][1] > w)
	{
		dp[0][2] = 2;
	}
	else
	{
		dp[0][2] = 1;
	}

	for (int i = 1; i < n; i++)
	{
		// �Ʒ� �� ���� �����ϰ� �� �ڸ��� �ϳ��� �δ� ���
		dp[i][0] = dp[i - 1][2] + 1;
		dp[i][1] = dp[i - 1][2] + 1;
		dp[i][2] = dp[i - 1][2] + 2;

		// �Ʒ��� �࿡�� ���η� �δ� ���
		if (nums[i][0] + nums[i - 1][0] <= w)
		{
			dp[i][0] = min(dp[i][0], dp[i - 1][1] + 1);
		}
		// ���� �࿡�� ���η� �δ� ���
		if (nums[i][1] + nums[i - 1][1] <= w)
		{
			dp[i][1] = min(dp[i][1], dp[i - 1][0] + 1);
		}
		// ���η� �� �� �ٽ� �ϳ� �δ� ���
		dp[i][2] = min(dp[i][2], min(dp[i][0] + 1, dp[i][1] + 1));
		// �� �� ���η� �� �� �ִ� ���
		if (nums[i][0] + nums[i - 1][0] <= w && nums[i][1] + nums[i - 1][1] <= w)
		{
			if (i == 1)
			{
				dp[1][2] = min(dp[1][2], 2);
			}
			else
			{
				dp[i][2] = min(dp[i][2], dp[i - 2][2] + 2);
			}
		}
		// ���η� �δ� ���
		if (nums[i][0] + nums[i][1] <= w)
		{
			dp[i][2] = min(dp[i][2], dp[i - 1][2] + 1);
		}
	}
	return dp[n - 1][2];
}

int solve(int n, int w, vector<vector<int> >& nums)
{
	int ans = INF;
	vector<vector<int> > copied = nums;

	// 0���̶� n - 1���� ���ÿ� ��ġ�� Ư���δ밡 ���� ��
	ans = min(ans, expand(n, w, copied));

	if (n > 1)
	{
		// 0���̶� n - 1���� �Ʒ����� ������ ��
		if (nums[0][0] + nums[n - 1][0] <= w)
		{
			copied[0][0] = w;
			copied[n - 1][0] = w;
			ans = min(ans, expand(n, w, copied) - 1);
		}
		copied[0][0] = nums[0][0];
		copied[n - 1][0] = nums[n - 1][0];

		// 0���̶� n - 1�� ������ ������ ��
		if (nums[0][1] + nums[n - 1][1] <= w)
		{
			copied[0][1] = w;
			copied[n - 1][1] = w;
			ans = min(ans, expand(n, w, copied) - 1);
		}
		copied[0][1] = nums[0][1];
		copied[n - 1][1] = nums[n - 1][1];

		// �Ʒ��� �� �� ��������
		if (nums[0][0] + nums[n - 1][0] <= w && nums[0][1] + nums[n - 1][1] <= w)
		{
			copied[0][0] = w;
			copied[n - 1][0] = w;
			copied[0][1] = w;
			copied[n - 1][1] = w;
			ans = min(ans, expand(n, w, copied) - 2);
		}
	}
	
	return ans;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	vector<int> ans(t);
	for(int i = 0; i < t; i++)
	{
		int n, w;
		cin >> n >> w;
		// nums[i][0] := i��° ���� �Ʒ���
		// nums[i][1] := i��° ���� ����
		vector<vector<int> > nums(n, vector<int>(2));
		for (int j = 0; j < n; j++)
		{
			cin >> nums[j][0];
		}
		for (int j = 0; j < n; j++)
		{
			cin >> nums[j][1];
		}

		ans[i] = solve(n, w, nums);
	}

	for (int i = 0; i < t; i++)
	{
		cout << ans[i] << '\n';
	}

	return 0;
}