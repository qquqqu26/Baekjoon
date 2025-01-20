#include <iostream>
#include <algorithm>
using namespace std;

int n;
int arr[100001];
int id1, id2;
long int minimum = 2000000000; //양수로 싹 맞춰 크기 비교 진행 1000000000

void saveIndex(int left, int right) {
	id1 = left;
	id2 = right;
}

void solution() {
	int left = 1;
	int right = n;

	while (left != right) {
		long int sum = arr[left] + arr[right];

		if (sum == 0) {
			saveIndex(left, right);
			break;
		}
		else if (sum < 0) {
			//갱신되는 경우
			if (-sum <= minimum) {
				minimum = -sum;
				saveIndex(left, right);
			}
			left++;
		}
		else {
			//갱신되는 경우
			if (sum <= minimum) {
				minimum = sum;
				saveIndex(left, right);
			}
			right--;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	//입력
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
	}

	//배열 정렬&로직 실행
	sort(arr + 1, arr + n + 1);
	solution();

	//출력
	cout << arr[id1] << " " << arr[id2];
}