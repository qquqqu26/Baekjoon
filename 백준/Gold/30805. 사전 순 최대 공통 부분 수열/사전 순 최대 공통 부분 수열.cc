//30805. 사전 순 최대 공통 부분 수열
//Binary Search

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {

	cin.tie(0);
	ios::sync_with_stdio(0);
	
	//입력
	const int maxSize = 101;
	int a[maxSize] = { 0 };
	int b[maxSize] = { 0 };
	int n, m;

	
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}

	cin >> m;
	for (int i = 1; i <= m; i++) {
		cin >> b[i];
	}
	

	//이진탐색
	int startA = 1;
	int endA = n;
	int* maxAddress = max_element(a+startA, a+endA+1);
	int maxA = *maxAddress;
	int aIndex = maxAddress - a;

	int startB = 1;
	int endB = m;
	maxAddress = max_element(b+startB, b + endB+1);
	int maxB = *maxAddress;
	int bIndex = maxAddress - b;

	vector<int> answer;

	while (maxA != 0 && maxB!=0) {
		//공통되는 가장 큰 값 찾기
		if (maxA > maxB) {
			a[aIndex] = 0;

			maxAddress = max_element( a+startA, a+endA+1);
			maxA = *maxAddress;
			aIndex = maxAddress - a;

			//cout << maxA << " " << aIndex << endl;
		}
		else if (maxA < maxB) {
			b[bIndex] = 0;

			maxAddress = max_element(b+startB, b + endB+1);
			maxB = *maxAddress;
			bIndex = maxAddress - b;
		}
		else {
			answer.push_back(maxA);

			startA = aIndex+1;
			startB = bIndex+1;

			maxAddress = max_element(a + startA, a + endA+1);
			maxA = *maxAddress;
			aIndex = maxAddress - a;
	
			maxAddress = max_element(b + startB, b + endB+1);
			maxB = *maxAddress;
			bIndex = maxAddress - b;

		}
	}

	//출력
	cout << answer.size() << "\n";
	//for(vector <int> a : answer) {
	for (auto i = 0; i < answer.size(); i++) {
		cout << answer[i] << " ";
	}
}