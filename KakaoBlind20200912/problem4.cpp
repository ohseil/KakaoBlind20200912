#include "problem4.h"

namespace problem4 {

	int solution(int n, int s, int a, int b, vector<vector<int>> fares) {

		// s, a, b에서 모든 노드까지의 최소경로를 다익스트라 알고리즘을 이용해 구한다.
		// s, a, b에서 각 노드까지의 거리 합중 제일 낮은 값이 답이다.

		long long answer = 0;

		map<int, map<int, int>> m;

		// fares 데이터를 바탕으로 각 노드에서 노드까지의 간선비용 데이터 map 생성.
		for (auto fare : fares) {
			m[fare[0]][fare[1]] = fare[2];
			m[fare[1]][fare[0]] = fare[2];
		}

		// 각 노드에서 모든 노드까지의 최소비용을 저장하기 위한 배열.
		long long dist[201][201];

		// 비용의 최대값으로 초기화
		for (int i = 0; i < 201; i++)
			for (int j = 0; j < 201; j++)
				dist[i][j] = 100000;

		// 데이터가 필요한 시작지점.
		int startPoints[3] = { s, a, b };

		// 시작지점에서 모든 노드까지의 최소비용 데이터 생성.
		for (int sp = 0; sp < 3; sp++) {

			// min heap.
			// pair.first -> 비용, pair.second -> 노드번호.
			priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

			// 시작지점 삽입
			int start = startPoints[sp];
			dist[start][start] = 0;
			pq.push(make_pair<long long, int>(0, (long long)startPoints[sp]));

			// 다익스트라 알고리즘.
			while (!pq.empty()) {

				pair<long long, int> data = pq.top();
				pq.pop();

				for (auto a : m[data.second]) {
					int node = a.first;
					int fare = a.second;

					if (dist[start][data.second] + fare < dist[start][node]) {
						// 현재 경로의 비용이 기존의 최소비용보다 적은 경우 갱신 후 heap 삽입.
						dist[start][node] = dist[start][data.second] + fare;
						pq.push(make_pair<long long, int>((long long)dist[start][node], (int)node));
					}
				}
			}
		}

		answer = dist[s][1] + dist[a][1] + dist[b][1];

		// s,a,b 임의의 노드까지의 최소거리 합중 제일 적은 값 탐색.
		for (int node = 1; node <= n; node++) {
			answer = min(answer, dist[s][node] + dist[a][node] + dist[b][node]);
		}

		return answer;
	}

	void execute() {

		int n = 7, s = 3, a = 4, b = 1;
		vector<vector<int>> fares;
		vector<int> v(3, 0);
		v[0] = 5; v[1] = 7; v[2] = 9;
		fares.push_back(v);
		v[0] = 4; v[1] = 6; v[2] = 4;
		fares.push_back(v);
		v[0] = 3; v[1] = 6; v[2] = 1;
		fares.push_back(v);
		v[0] = 3; v[1] = 2; v[2] = 3;
		fares.push_back(v);
		v[0] = 2; v[1] = 1; v[2] = 6;
		fares.push_back(v);

		cout << solution(n, s, a, b, fares) << endl;

	}
}