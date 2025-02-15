#include <iostream>
#include <stack>
#include <limits>
using namespace std;

const int maxSize = 11;
int matrix[maxSize][maxSize];
int n;

int minValue = numeric_limits<int>::max(); //최솟값
int sum = 0;
int visited[maxSize];
int numOfSelected;
int startCity;
stack<int> sss; //디버깅용 확인용의 stack이기에 없어도 됨.

void backtracking(int& lastCity) {
	for (int nextCity = 1; nextCity <= n; nextCity++) {

		if (numOfSelected == n) {
			if (matrix[lastCity][startCity] != 0) {
				sum += matrix[lastCity][startCity];
				minValue = min(sum, minValue);
				sum -= matrix[lastCity][startCity];
			}
			
			
			return;
		}
		
		if (matrix[lastCity][nextCity] == 0 || visited[nextCity] == true) 
			continue;

		sss.push(nextCity);
		numOfSelected++;
		sum += matrix[lastCity][nextCity];
		visited[nextCity] = true;

		backtracking(nextCity);
		numOfSelected--;
		sum -= matrix[lastCity][nextCity];
		visited[nextCity] = false;
		sss.pop();

	}
}

int main() {

	cin.tie(0); cout.tie(0);
	ios::sync_with_stdio(0);

	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> matrix[i][j];
		}
	}

	for (int i = 1; i <= n; i++) {
		startCity = i;
		visited[startCity] = true;
		sss.push(startCity);
		numOfSelected++;
		backtracking(startCity);
		visited[startCity] = false;
		sss.pop();
		numOfSelected--;
	}

	cout << minValue;

} 
