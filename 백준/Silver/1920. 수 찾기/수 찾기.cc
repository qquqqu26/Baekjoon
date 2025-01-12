#include <iostream>
#include <algorithm>
using namespace std;

int main() {

	cin.tie(0);
	ios::sync_with_stdio(0);
	
	const int maxSize = 100001;
	int n, m;
	int a[maxSize];
	bool answer[maxSize] = { 0 };

	//입력
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}

	sort(a+1, a+n+1);

	cin >> m;
	for (int i = 1; i <= m; i++) {
		int input;
		cin >> input;

		//이진 탐색
		int start = 1;
		int end = n;
		int mid = (start + end) / 2;

		while (start <= end) {
			if (input > a[mid]) {
				start = mid + 1;
				mid = (start + end) / 2;
			}
			else if (input < a[mid]) {
				end = mid - 1;
				mid = (start + end) / 2;

			}
			else {
				answer[i] = 1;
				break;
			}
		}
	}

	//출력
	for (int i = 1; i <= m; i++) {
		cout << answer[i] << "\n";
	}

}