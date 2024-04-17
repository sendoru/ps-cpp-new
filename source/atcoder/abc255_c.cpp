#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <queue>
typedef long double ld;
typedef long long ll;
const ld INF = 1e9;
using namespace std;

int main(void)
{
	ll x, a, d, n;
	cin >> x >> a >> d >> n;

	// ���� S: a�� ����, d�� ����, n�� �� ����
	// x�� S�� ���ҿ��� ��
	// S�� ������ ��: a + (n - 1) * d

	if (d == 0)
	{
		cout << abs(x - a);
		return 0;
	}

	if (d < 0)
	{
		ll newA = a + (n - 1) * d;
		ll newD = -d;

		a = newA;
		d = newD;
	}

	// ���� S�� ������ ���������̴�
	if (x < a)
		cout << abs(x - a);

	else if (x > a + (n - 1) * d)
		cout << abs(x - (a + (n - 1) * d));

	// x�� S�� �ּڰ��� �ִ� ������ ���
	else
	{
		x -= a;
		a = 0;
		ll ans = x % d;
		ans = min(ans, d - ans);
		cout << ans;
	}
	return 0;
}