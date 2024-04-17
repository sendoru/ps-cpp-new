#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
typedef long long ll;

int main(void)
{
	int t;
	cin >> t;
	while (t--)
	{
		ll n2, n3, n4;
		cin >> n2 >> n3 >> n4;
		ll ans = 0;
		/*
		* 10 = 2 + 2 + 2 + 2 + 2
		*    = 2 + 2 + 2 + 4
		*    = 2 + 2 + 3 + 3 = 2 + 2 + 6
		*    = 2 + 4 + 4
		*    = 3 + 3 + 4 = 4 + 6
		*/

		// ���� 3¥�� 2���� ���ļ� ���� 6¥���� ����
		n3 /= 2;

		// 4 + 6�� ��� ���� ó��
		ans += min(n3, n4);
		n3 -= ans;
		n4 -= ans;

		// 4¥���� �ϳ��� �ȳ������, 2¥�� 5�� �Ǵ� 2 + 2 + 6�� ����
		if (n4 == 0)
		{
			ll addi = min(n2 / 2, n3);
			ans += addi;
			n2 -= addi * 2ll;
			n3 -= addi;
			// 2 + 2 + 6�� ���� ����� 2¥���� ������� 2¥�� 5���� ����
			// 6¥���� �������� �ƹ��͵�����
			if (n2 != 0)
			{
				ans += n2 / 5;
			}
		}

		// 6¥���� �ϳ��� �ȳ������, 2¥�� 5��, 2 + 2 + 2 + 4, 2 + 4 + 4�� ����
		// ���ʺ��� ó��
		else
		{
			ll addi = min(n2, n4 / 2);
			ans += addi;
			n2 -= addi;
			n4 -= addi * 2;
			// n4�� �ȳ������� 2 * 5�� ����
			if (n4 == 0)
			{
				ans += n2 / 5;
			}
			// n4�� 1�� �������� 
			else if (n4 == 1)
			{
				if (n2 >= 3)
				{
					n2 -= 3;
					n4 = 0;
					ans++;
				}
				ans += n2 / 5;
			}
			// n4�� 2�� �̻� ���� ���� �� �̻� ������
		}

		cout << ans << '\n';
	}

	return 0;
}