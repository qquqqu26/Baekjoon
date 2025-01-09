#include <iostream>
#include <vector>
using namespace std;
int n, x;
vector<int> answer;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> x;
	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;

		if (num < x) {
			answer.push_back(num);
		}
	}

	for(int cur = 0; cur < answer.size(); cur++) {
		cout << answer[cur] << " ";
	}
}