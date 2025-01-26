//문제 번호problem, 난이도level:100개, 알고리즘 분류group 100개

#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <vector>
using namespace std;

unordered_map<int, pair<int, int>> problemMap; // 문제번호, 난이도, 분류
map<int, set<int>> levelMap; // 난이도, 문제
unordered_map<int, map<int, set<int>>> groupMap; // 분류, 난이도, 문제번호
vector<int> answer;

/*
void print(int x) {
	if (x == 1) {
		for (auto pair : levelMap) {
			cout << "\n난이도: " << pair.first << ", 문제: " << pair.second.;
		}
	}
	else if (x == 2) {
		for (auto pair : problemMap) {
			cout << "\n난이도: " << pair.first << ", 문제: " << pair.second;
		}
	}
	else if (x == 3) {
		for (auto pair : problemMap) {
			cout << "\n난이도: " << pair.first << ", 문제: " << pair.second;
		}
	}
}
*/

//분류 범위 내 최대최소
void recommend(int& group, int& x) {
	if (x == 1) {
		answer.push_back(*groupMap[group].rbegin()->second.rbegin());
	}
	else if (x == -1) {
		answer.push_back(*groupMap[group].begin()->second.begin());
	}
}

//최대최소
void recommend2(int& x) {
	if (x == 1) {
		answer.push_back(*levelMap.rbegin()->second.rbegin());
	}
	else if (x == -1) {
		answer.push_back(*levelMap.begin()->second.begin());
	}
}

//난이도 검색, 범위 내 최대 최소
void recommend3(int& x, int& level) {
	auto it = levelMap.lower_bound(level);
	if (x == 1) {
		if (it == levelMap.end()) {
			answer.push_back(-1);
		}
		else {
			answer.push_back(*it->second.begin());
		}
	}
	else if (x == -1) {
		if (it == levelMap.begin()) {
			answer.push_back(-1);
		}
		else {
			it--;
			answer.push_back(*it->second.rbegin());
		}
	}
}

void add(int& problem, int& level, int& group) {
	problemMap[problem].first = level;
	problemMap[problem].second = group;
	levelMap[level].emplace(problem);
	groupMap[group][level].emplace(problem);
}

void solved(int& problem) {
	int level = problemMap[problem].first;
	int group = problemMap[problem].second;
	problemMap.erase(problem);
	levelMap[level].erase(problem); //레벨맵, 값 지우기
	if (levelMap[level].empty()) {
		levelMap.erase(level); //레벨맵, 키 지우기
	}
	groupMap[group][level].erase(problem);
	if (groupMap[group][level].empty()) {
		groupMap[group].erase(level);
		if (groupMap[group].empty()) {
			groupMap.erase(group);
		}
	}
}

int main() {

	cin.tie(0); cout.tie(0);
	ios::sync_with_stdio(0);

	//입력
	int n;
	cin >> n;
	int P, L, G;
	for (int i = 0; i < n; i++) {
		cin >> P >> L >> G;
		add(P, L, G);
	}


	int m;
	cin >> m;
	string command;
	int n1, n2, n3;
	
	for (int i = 0; i < m; i++) {
		cin >> command >> n1;
		if (command == "recommend") {
			cin >> n2;
			recommend(n1, n2);
		}
		else if (command == "recommend2") {
			recommend2(n1);
		}
		else if (command == "recommend3") {
			cin >> n2;
			recommend3(n1, n2);
		}
		else if (command == "add") {
			cin >> n2 >> n3;
			add(n1, n2, n3);
		}
		else if (command == "solved") {
			solved(n1);
		}
	}

	//출력
	for (int it : answer) {
		cout << it << "\n";
	}

}