#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>
using namespace std;
typedef long long ll;
typedef long double ld;

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
		cout << "Case #" << t << ": ";
		cout << (possible ? "POSSIBLE" : "IMPOSSIBLE");
		cout << '\n';
	}

	return 0;
}