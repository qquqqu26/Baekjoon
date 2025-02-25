#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> containers;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int k, n, volume, result = 0;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> volume;
		containers.push_back(volume);
	}

	sort(containers.begin(), containers.end());

	long long left = 1;
	long long right = *(containers.end()-1);
	long long mid;

	int quotient;
	while (left <= right) {
		mid = (left + right) / 2;
		quotient = 0;

		for (int _container : containers) {
			quotient += (_container / mid);
		}

		if (quotient >= k) {
			result = mid;
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}

	}

	cout << result;
}