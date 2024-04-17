#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>
using namespace std;
typedef long long ll;
typedef long double ld;

bool naiveSolve(int n, string s)
{
	bool possible = false;
	if (n < 5)
	{
		possible = true;
	}
	else
	{
		for (int i = 0; i < (1 << n); i++)
		{
			bool curPossible = true;
			for (int j = 0; j < n; j++)
			{
				if (s[j] != '?' && (i >> j) % 2 + '0' != s[j])
				{
					curPossible = false;
					break;
				}
			}
			if (!curPossible)
			{
				continue;
			}
			// ���� 5�� �Ӹ���� Ȯ��
			for (int j = 0; j < n - 4; j++)
			{
				if ((i >> j) % 2 == (i >> (j + 4)) % 2 && (i >> (j + 1)) % 2 == (i >> (j + 3)) % 2)
				{
					curPossible = false;
					break;
				}
			}
			if (!curPossible)
			{
				continue;
			}
			// ���� 6�� �Ӹ���� Ȯ��
			for (int j = 0; j < n - 5; j++)
			{
				if ((i >> j) % 2 == (i >> (j + 5)) % 2 && (i >> (j + 1)) % 2 == (i >> (j + 4)) % 2 && (i >> (j + 2)) % 2 == (i >> (j + 3)) % 2)
				{
					curPossible = false;
					break;
				}
			}
			if (curPossible)
			{
				possible = true;
				break;
			}
		}
	}

	return possible;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++)
	{
		int n;
		cin >> n;
		string s;
		cin >> s;
		bool possible = false;

		// ���� 5 �̻��� �Ӹ������ �ִ� = ���� 5 �Ǵ� 6�� �Ӹ������ �ִٿ� ��ġ
		// ���� n (n >= 3)�� �Ӹ������ ������ �� �Ӹ������ �κй��ڿ��� ���� n-2¥�� �Ӹ���ҵ� �����ϱ� ����
		// ���׳� ����...
		if (n < 15)
		{
			possible = naiveSolve(n, s);
		}
		else
		{
			// dp6[i][j] := i - 4 ~ i��° ���ڸ� j(������)���� ����� ������ �� �����ϸ� true, �ƴϸ� false
			vector<vector<bool>> dp6(n, vector<bool>(64, false));
			for (int i = 0; i < 64; i++)
			{
				if ((((i >> 0) % 2 == (i >> 5) % 2) && ((i >> 1) % 2 == (i >> 4) % 2) && ((i >> 2) % 2 == (i >> 3) % 2)) || (((i >> 0) % 2 == (i >> 4) % 2) && ((i >> 1) % 2 == (i >> 3) % 2)) || (((i >> 1) % 2 == (i >> 5) % 2) && ((i >> 2) % 2 == (i >> 4) % 2)))
				{
					continue;
				}
				else
				{
					bool matched = true;
					for (int j = 0; j < 6; j++)
					{
						if (s[j] != '?' && (i >> (5 - j)) % 2 + '0' != s[j])
						{
							matched = false;
							break;
						}
					}
					if (!matched)
					{
						continue;
					}
					else
					{
						dp6[5][i] = true;
					}
				}
			}

			for (int i = 6; i < n; i++)
			{
				for (int j = 0; j < 64; j++)
				{
					if ((((j >> 0) % 2 == (j >> 5) % 2) && ((j >> 1) % 2 == (j >> 4) % 2) && ((j >> 2) % 2 == (j >> 3) % 2)) || (((j >> 0) % 2 == (j >> 4) % 2) && ((j >> 1) % 2 == (j >> 3) % 2)) || (((j >> 1) % 2 == (j >> 5) % 2) && ((j >> 2) % 2 == (j >> 4) % 2)))
					{
						continue;
					}
					else
					{
						bool matched = true;
						for (int k = 0; k < 6; k++)
						{
							if (s[i + k - 5] != '?' && (j >> (5 - k)) % 2 + '0' != s[i + k - 5])
							{
								matched = false;
								break;
							}
						}
						if (!matched)
						{
							continue;
						}
						else
						{
							dp6[i][j] = dp6[i - 1][j >> 1] || dp6[i - 1][(j >> 1) + 32];
						}
					}
				}
			}

			possible = false;
			for (int i = 0; i < 64; i++)
			{
				if (dp6[n - 1][i])
				{
					possible = true;
					break;
				}
			}
		}


		cout << "Case #" << t << ": ";
		cout << (possible ? "POSSIBLE" : "IMPOSSIBLE");
		cout << '\n';
	}

	return 0;
}