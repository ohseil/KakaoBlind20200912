#include "problem4.h"

namespace problem4 {

	int solution(int n, int s, int a, int b, vector<vector<int>> fares) {

		// s, a, b���� ��� �������� �ּҰ�θ� ���ͽ�Ʈ�� �˰����� �̿��� ���Ѵ�.
		// s, a, b���� �� �������� �Ÿ� ���� ���� ���� ���� ���̴�.

		long long answer = 0;

		map<int, map<int, int>> m;

		// fares �����͸� �������� �� ��忡�� �������� ������� ������ map ����.
		for (auto fare : fares) {
			m[fare[0]][fare[1]] = fare[2];
			m[fare[1]][fare[0]] = fare[2];
		}

		// �� ��忡�� ��� �������� �ּҺ���� �����ϱ� ���� �迭.
		long long dist[201][201];

		// ����� �ִ밪���� �ʱ�ȭ
		for (int i = 0; i < 201; i++)
			for (int j = 0; j < 201; j++)
				dist[i][j] = 100000;

		// �����Ͱ� �ʿ��� ��������.
		int startPoints[3] = { s, a, b };

		// ������������ ��� �������� �ּҺ�� ������ ����.
		for (int sp = 0; sp < 3; sp++) {

			// min heap.
			// pair.first -> ���, pair.second -> ����ȣ.
			priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

			// �������� ����
			int start = startPoints[sp];
			dist[start][start] = 0;
			pq.push(make_pair<long long, int>(0, (long long)startPoints[sp]));

			// ���ͽ�Ʈ�� �˰���.
			while (!pq.empty()) {

				pair<long long, int> data = pq.top();
				pq.pop();

				for (auto a : m[data.second]) {
					int node = a.first;
					int fare = a.second;

					if (dist[start][data.second] + fare < dist[start][node]) {
						// ���� ����� ����� ������ �ּҺ�뺸�� ���� ��� ���� �� heap ����.
						dist[start][node] = dist[start][data.second] + fare;
						pq.push(make_pair<long long, int>((long long)dist[start][node], (int)node));
					}
				}
			}
		}

		answer = dist[s][1] + dist[a][1] + dist[b][1];

		// s,a,b ������ �������� �ּҰŸ� ���� ���� ���� �� Ž��.
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