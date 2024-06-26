#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;

ll sumofM(ll n, ll m)
{
	if (n < 0 || (n <= 9 && n < m))
	{
		return 0;
	}
	if (n <= 9 && n >= m)
	{
		return 1;
	}

	ll lg = (ll)log10l(n);

	ll lower = powl(10ll, lg) - 1;
	ll ret = 0;
	ll highestDigit = n / (lower + 1);

	ret += highestDigit * lg * (ll)powl(10ll, lg - 1);
	if (m == 0)
	{
		for (int i = lg - 1; i >= 0; i--)
		{
			if ((ll)powl(10, i) - 1 >= n % (lower + 1))
			{
				ret -= (ll)powl(10ll, i) - 1 - n % (lower + 1);
			}
		}
	}

	if (highestDigit == m && m != 0)
	{
		ret += n % (lower + 1) + 1;
	}
	else if (highestDigit > m && m != 0)
	{
		ret += lower + 1;
	}
	ret += sumofM(n - highestDigit * (lower + 1), m);

	return ret;
}

int main(void)
{
	ll n;
	cin >> n;
	for (int i = 0; i <= 9; i++)
	{
		if (i == 0)
		{
			cout << sumofM(n, i) - 1 << ' ';
		}
		else
		{
			cout << sumofM(n, i) << ' ';
		}
	}
	return 0;
}