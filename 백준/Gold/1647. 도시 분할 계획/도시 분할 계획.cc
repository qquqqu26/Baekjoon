//1647번. 도시분할 계획
//Prim's MST(Priority Queue)

#include <iostream>
#include <queue>
#include <tuple>
using namespace std;

const int maxHouses = 100001;
int house, road;

vector< pair<int, int> > roads[maxHouses]; //정점 별 간선 정보: {비용, 연결된 상대정점}
priority_queue< tuple<int, int, int>> connectedRoads; //연결한 간선 정보: {비용, 정점1 ,정점2}

bool visited[maxHouses] = { false };
int numOfEdge[maxHouses] = { 0 };

int minCost = 0;
void Prim_MST(int h) {
	priority_queue< tuple<int, int, int>, 
		vector< tuple<int, int, int> >,
		greater< tuple<int, int, int> >>  pq;

	int h1, h2, cost;

	//집 h에 연결된 길 pq에 저장
	visited[h] = 1;
	for (auto cur : roads[h]) {
		cost = cur.first;
		h2 = cur.second;
		pq.push({ cost, h, h2 });
		//cout << cost << ": " << h << " " << h2 << endl;
	}


	while (connectedRoads.size() <= house - 1) {

		if (pq.empty()) {
			return;
		}

		auto top = pq.top();
		cost = get<0>(top);
		h1 = get<1>(top);
		h2 = get<2>(top);
		pq.pop();

		if (visited[h2]) //방문했던 정점은 무시
			continue;
		else {
			visited[h2] = 1;
			minCost += cost;
			//cout << "비용: " << cost << "\n";
			connectedRoads.push({ cost, h1, h2 });
			numOfEdge[h1]++;
			numOfEdge[h2]++;

			for (auto cur : roads[h2]) {
				if (!visited[cur.second]) {
					cost = cur.first;
					pq.push({ cost, h2, cur.second });
				}
			}
		}
	}
	
}


int main() {

	cin.tie(0);
	ios::sync_with_stdio(0);

	//입력
	cin >> house >> road;
	int h1, h2, cost;
	for (int i = 1; i <= road; i++) {
		cin >> h1 >> h2 >> cost;
		
		roads[h1].push_back({ cost, h2 });
		roads[h2].push_back({ cost, h1 });
	}

	Prim_MST(1); //첫 번째 집부터 탐색

	/*출력
	for (int i = 1; i <= house; i++) {
		cout << "\n" << i << "에 연결된 집\n";
		while (!roads[i].empty()) {
			cout << "비용: " << roads[i].top().first << " 대상 집:" << roads[i].top().second << endl;
			roads[i].pop();
		}
	}
	*/

	//마을 분리하기
	minCost -= get<0>(connectedRoads.top());

	cout << minCost << endl;
}