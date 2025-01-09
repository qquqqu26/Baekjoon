#include <iostream>
#include <queue>
using namespace std;
queue<string> answer;
priority_queue<int> line;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int a, b, c;
	cin >> a >> b >> c;
	
	while (a != 0) {
		line.push(a);
		line.push(b);
		line.push(c);

		c = line.top();
		line.pop();		
		a = line.top();
		line.pop();		
		b = line.top();
		line.pop();
		
		if (c*c == a*a + b*b) {
			answer.push("right");
		}
		else {
			answer.push("wrong");
		}
		cin >> a >> b >> c;
	}

	while (!answer.empty()) {
		cout << answer.front() << "\n";
		answer.pop();
	}
}