#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int maxSize = 51;
int matrix[maxSize][maxSize];
int backupMatrix[maxSize][maxSize]; //초기 먼지량 백업하는 배열
int r, c, t = 0;

int purifierR1, purifierR2; //청정기 y좌표

void backup() {
	for (int y = 1; y <= r; y++)
		memcpy(&backupMatrix[y], &matrix[y], sizeof(int)*(c+2) );
}

void spreadDust() {
	backup();
	
	pair<int, int> direction[4] = { {-1, 0}, {1, 0}, {0 ,-1}, {0, 1} };

	for (int y = 1; y <= r; y++) {
		for (int x = 1; x <= c; x++) {

			if (backupMatrix[y][x] <= 0) continue;

			int spreadAmount = (backupMatrix[y][x]) / 5;
			for (pair<int, int> dir : direction) {
				int dirX = x + dir.second;
				int dirY = y + dir.first;

				//확산 가능한 지 확인
				if (dirX > 0 && dirX <= c && dirY > 0 && dirY <= r
					&& matrix[dirY][dirX] >= 0) {

					matrix[dirY][dirX] += spreadAmount;
					matrix[y][x] -= spreadAmount;

				}
			}
		}
	}
}

void purifyAir() {
	backup();

	//반시계 방향 순환(가로는 memcpy, 세로는 for문)
	matrix[purifierR1][2] = 0;
	memcpy(&matrix[purifierR1][3], &backupMatrix[purifierR1][2], sizeof(int) * (c - 2)); //right
	for (int y = purifierR1 - 1; y >= 1; y--) matrix[y][c] = backupMatrix[y + 1][c]; //up
	memcpy(&matrix[1][1], &backupMatrix[1][2], sizeof(int) * (c - 1)); //left
	for (int y = 2; y < purifierR1; y++) matrix[y][1] = backupMatrix[y - 1][1]; //down


	//시계 방향 순환
	matrix[purifierR2][2] = 0;
	memcpy(&matrix[purifierR2][3], &backupMatrix[purifierR2][2], sizeof(int) * (c - 2));
	for (int y = purifierR2 + 1; y <= r; y++) matrix[y][c] = backupMatrix[y - 1][c];
	memcpy(&matrix[r][1], &backupMatrix[r][2], sizeof(int) * (c - 1));
	for (int y = r - 1; y > purifierR2; y--) matrix[y][1] = backupMatrix[y + 1][1];

}

int solution(int day) {

	while (day != 0) {

		spreadDust();
		purifyAir();

		day--;
	}
	
	//먼지 계산
	int answer = 0;
	for (int y = 1; y <= r; y++) {
		for (int x = 1; x <= c; x++) {
			if (matrix[y][x] > 0)
				answer += matrix[y][x];
		}
	}

	return answer;
}

int main() {

	cin.tie(0);
	ios::sync_with_stdio(0);

	//입력
	cin >> r >> c >> t;

	for (int y = 1; y <= r; y++) {
		for (int x = 1; x <= c; x++) {
			cin >> matrix[y][x];

			//(아래)공기청정기 좌표
			if (matrix[y][x] == -1) purifierR2 = y;
		}
	}
	purifierR1 = purifierR2 - 1; //위 공기청정기 좌표

	cout << solution(t);

	return 0;
}