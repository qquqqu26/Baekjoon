#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

//나중에 구조체로 해보자

int startX; int startY;
int endX; int endY;
vector<int> answer;

int cnt;
void countPlanetTransitions(int& x, int& y, int& r) {
	//원이 출발점과 도착점을 포함하는 지
	bool isStartInCircle = (pow(startX - x, 2) + pow(startY - y, 2) < pow(r, 2));
	bool isEndInCircle = (pow(endX - x, 2) + pow(endY - y, 2) < pow(r, 2));

	if (isStartInCircle != isEndInCircle) {
		cnt++;
	}


}
int main() {

	cin.tie(0); cout.tie(0);
	ios::sync_with_stdio(0);

	//입력
	int t;
	cin >> t;

	int n;
	int x, y, r;
	for (int i = 0; i < t; i++) {
		cin >> startX >> startY >> endX >> endY;
		cin >> n;

		cnt = 0;
		for (int j = 1; j <= n; j++) {
			cin >> x >> y >> r;
			countPlanetTransitions(x, y, r);
		}
		answer.push_back(cnt);
	}

	//출력
	for (int it : answer) {
		cout << it << "\n";
	}
}