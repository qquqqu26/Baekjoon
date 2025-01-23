#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

map<int, set<int>> Lsearch; // 난이도, 문제번호
map<int, int> Psearch; // 문제번호, 난이도
vector<int> answer;

void recommend(int& x) {
	if (x == 1) {
		auto &s = Lsearch.rbegin()->second;
		answer.push_back(*s.rbegin());
	}
	else if (x == -1) {
		auto &s = Lsearch.begin()->second;
		answer.push_back(*s.begin());
	}
}

void solved(int& problem) {

	int level = Psearch[problem]; //난이도 추출rbegin
	auto &s = Lsearch[level]; //해당 set 추출
	s.erase(problem); //문제 키 삭제
	if (s.size() == 0) Lsearch.erase(level); //난이도 키 삭제
	Psearch.erase(problem);

}

void add(int& problem, int& level) {
	Lsearch[level].insert(problem);
	Psearch.emplace(problem, level);
}

int main() {

	cin.tie(0); cout.tie(0);
	ios::sync_with_stdio(0);

	//입력
	int n, m;
	cin >> n;
	int P, L;
	for (int i = 0; i < n; i++) {
		cin >> P >> L;
		Lsearch[L].insert(P);
		Psearch.emplace(P, L);
	}

	cin >> m;
	string command;
	int num;
	for (int i = 0; i < m; i++) {
		cin >> command >> num;
		if (command == "recommend") {
			recommend(num);
		}
		else if (command == "solved") {
			solved(num);
		}
		else if (command == "add") {
			cin >> L;
			add(num, L);
		}
	}

	//출력
	for (auto it : answer) {
		cout << it << "\n";
	}
}