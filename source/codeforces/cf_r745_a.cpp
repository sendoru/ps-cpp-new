#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
typedef long long ll;
constexpr ll MOD = 1000000007;

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
		// ���� 2n
		// p[i] < p[i + 1]�� i ������ �ּ� n��
		// ��: ((2n)! / 2) % MOD
		ll ans = 1;
		for (ll i = 3; i <= 2 * n; i++)
		{
			ans %= MOD;
			ans *= i;
		}
		ans %= MOD;
		cout << ans << '\n';
	}
	return 0;
}