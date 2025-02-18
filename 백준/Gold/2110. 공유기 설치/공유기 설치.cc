#include <iostream>
#include <algorithm>
using namespace std;

const int maxHouse = 200001;
int house[maxHouse];
int n, c;

int first;
int last;
int gap;
int router;
int* it;
int answer;

void binarySearch() {
	int low = 1;
	int high = house[n] - house[1]; //8

	while (high >= low) {
		//초기화
		gap = (low + high) / 2;
		router = 1; //1번 집에 공유기 설치
		first = 1;
		last = n;
		it = NULL;
		

		//공유기 시범 설치
		while (router < c) {
			it = lower_bound(house+first, house + n +1, house[first] + gap);
			if (it == house + n + 1) 
				break;

			first = it - house;
			router++;
		}

		if (router == c) {
			 /*설치한 공유기가 적정(많다)
			 =>설치할 공유기router 줄이기
			 =>널널하게 gap널리기
			 */
			
			answer = gap;
			low = gap + 1;

			/*이 케이스에서만 answer갱신하는 이유
			* 공유기가 기준보다 많은 경우에만 답 가능성 있어서
			*/
		}
		else { //router > c
			/*router > c
			=>설치한 공유기가 모자르다
			=>설치할 공유기router 늘리기
			=>촘촘하게 gap좁히기
			*/

			high = gap - 1;

		}
	}
}

int main() {
	
	//입력
	cin >> n >> c;
	for (int i = 1; i <= n; i++) {
		cin >> house[i];
	}
	sort(house+first, house+n+1);
	
	//이분 탐색
	binarySearch();

	cout << answer;
}