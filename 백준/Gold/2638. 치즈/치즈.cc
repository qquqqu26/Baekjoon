//1. BFS<<<<
//2. 시뮬레이션?
#include <iostream>
#include <queue>
using namespace std;

const int maxSize = 101;
const int numOfGrid = maxSize * maxSize;

int n, m;
int grid[maxSize][maxSize];
//grid: 치즈[양의 정수=>녹는 시간], 외부 공기[0], 내부 공기[음의 정수=>소속공기개수?]
bool visited[maxSize][maxSize];

queue<pair<int, int>> cheese; 
queue<pair<int, int>> updateQ; //좌표(x, y) 

pair<int, int> air[numOfGrid]; //내부 공기의 시작점을 담은 배열
int numOfAir = 0;

pair<int, int> direction[4] = { {-1, 0}, {1, 0}, {0, -1} ,{0, 1} }; //상, 하, 좌, 우
int dirR, dirC;
int dirR2, dirC2;
int hour, adjacentCount, out;

bool isInBounds(int& r, int& c) {
	if (r > 0 && r <= n && c > 0 && c <= m) return true;
	else return false;
}

bool willMelt(int& r, int& c) {
	adjacentCount = 0;

	for (auto& dir : direction) {

		dirR2 = r + dir.first;
		dirC2 = c + dir.second;
		if (!isInBounds(dirR2, dirC2)) continue;

		out = grid[dirR2][dirC2];
		// 0 <= out < hour 이면 녹을 예정
		if (out >= 0 && out < hour) adjacentCount++;

		//조기 종료
		if (adjacentCount == 2) return true;

	}
	return false;
}

void bfs(int& startR, int&startC, string func) {
	queue<pair<int, int>> q;
	int frontR, frontC;

	q.push({ startR, startC });

	while (!q.empty()) {
		frontR = q.front().first;
		frontC = q.front().second;

		if (func == "countInnerSpaces") {
			visited[frontR][frontC] = 1;
			grid[frontR][frontC] = -numOfAir;
		}
		else if (func == "releaseEnclosedArea") {
			grid[frontR][frontC] = 0;
		}
		

		//사방탐색
		for (auto& dir : direction) {
			dirR2 = frontR + dir.first;
			dirC2 = frontC + dir.second;
			if (!isInBounds(dirR2, dirC2)) continue;

			//내부 공간 탐색용
			if (func == "countInnerSpaces") {

				if (!visited[dirR2][dirC2]) {
					q.push({ dirR2, dirC2 });
					grid[dirR2][dirC2] = -numOfAir;
					visited[dirR2][dirC2] = 1;
				}
			}
			//내부 공간 해제용
			else if (func == "releaseEnclosedArea") { 
				if (grid[dirR2][dirC2] < 0) q.push({ dirR2, dirC2 });

			}
		}
		
		q.pop();
	}

}

int main() {

	cin.tie(0); cout.tie(0);
	ios::sync_with_stdio(0);

#pragma region Input
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> grid[i][j];
			
			if (grid[i][j] == 1) {
				visited[i][j] = 1; //치즈는 방문처리
				grid[i][j] = numOfGrid; //hour의 최대치?로
				cheese.push({ i, j });
			}
		}
	}
#pragma endregion

	int r, c, answer = 0;
//갇힌 공기 세고 stack 배열 저장
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			
			if (!visited[i][j]) {
				air[numOfAir] = { i, j }; //공기 시작점
				
				bfs(i, j, "countInnerSpaces");

				numOfAir++;
			}
		}
	}

	hour = 1;
	int size;
	while (!cheese.empty()) {
		size = cheese.size();

		//1. queue순환하며 녹을 치즈 업데이트큐에 저장
		while (size > 0) {

			r = cheese.front().first;
			c = cheese.front().second;

			//치즈큐 초기화: 모든 치즈 조각 -> 녹을 치즈 조각만 담음
			if (willMelt(r, c)) {
				updateQ.push({ r, c });
				
			}
			else {
				//맨뒤로 보내기
				cheese.push({ r, c });
			}

			cheese.pop();
			size--;
		}
		
		//2. 시간별 업데이트
		while(!updateQ.empty())
		{
			r = updateQ.front().first;
			c = updateQ.front().second;
			updateQ.pop();

			//치즈 녹이기
			grid[r][c] = hour;
			answer = hour;

			//3. 내부 공간 해제
			for (auto& dir : direction) {
				dirR = r + dir.first;
				dirC = c + dir.second;

				if (grid[dirR][dirC] < 0) {
					bfs(dirR, dirC, "releaseEnclosedArea");
				}
			}
		
		}

		hour++;
	}

	//출력
	cout << answer;
} 