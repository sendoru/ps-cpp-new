#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

int main(void)
{
	ll n, k, distance = 0;
	cin >> n >> k;
	// friends[i] = {ģ���� ��ġ, ģ���� ������ �ִ� ��}
	vector<pair<ll, ll> > friends(n);
	for (int i = 0; i < n; i++)
	{
		cin >> friends[i].first >> friends[i].second;
	}
	sort(friends.begin(), friends.end());
	ll prevFriend = 0;
	for (int i = 0; i < n; i++)
	{
		ll nextFriendDistance = friends[i].first - prevFriend;
		if (nextFriendDistance > k)
		{
			distance += k;
			k = 0;
			break;
		}
		else
		{
			distance += nextFriendDistance;
			k -= nextFriendDistance;
			k += friends[i].second;
			prevFriend = friends[i].first;
		}
	}
	distance += k;
	cout << distance << '\n';
	return 0;
}