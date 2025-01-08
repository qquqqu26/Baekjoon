//11047번. 동전 0
//Greedy

#include <iostream>

using namespace std;

int n, k, minCount;
const int coinSize = 11;
int divisor[coinSize];

void Greedy(int k) {
	int quotient;

	for (int i = n; i > 0; i--) { //역순으로 나누기
		quotient = k / divisor[i];
		if (quotient > 0) {
			minCount += quotient;
			k %= divisor[i];
		}
	}
}

int main() {

	cin.tie(0);
	ios::sync_with_stdio(0);

	//입력
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> divisor[i];
	}

	Greedy(k);

	cout << minCount << endl;
}