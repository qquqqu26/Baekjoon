//11047번. 동전 0
//Greedy

#include <iostream>

using namespace std;

int n, k, minCount;
const int coinSize = 11;
int divisor[coinSize];

void Greedy(int k) {
	for (int i = n; i > 0; i--) { //역순으로 나누기
		minCount += k / divisor[i];
		k %= divisor[i];
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