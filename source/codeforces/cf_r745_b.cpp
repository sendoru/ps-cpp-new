#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main(void)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;
	while (t--)
	{
		ll n, m, k;
		cin >> n >> m >> k;
		bool ans = false;
		// ���� �׷����� ����� ���� �ּ����� ���� ���� mMin = n - 1;
		// �ִ����� ���� ���� mMax = n * (n - 1) / 2
		if (m < n - 1 || m > n * (n - 1) / 2ll)
			ans = false;

		// ��� ��쿡�� ������ 2 ���Ϸ� ���� �� ����
		else if (k >= 4)
			ans = true;

		// ������ 1�� �Ƿ��� ��� ������ �ٸ� ������ ���� ������־�� ��
		// �� m == n * (n - 1) / 2
		else if (k == 3 && m == n * (n - 1) / 2)
			ans = true;

		// ������ 0�� �Ƿ��� ������ �ϳ����� ��
		else if (k == 2 && n == 1)
			ans = true;

		cout << (ans ? "YES" : "NO") << '\n';
	}
	return 0;
}