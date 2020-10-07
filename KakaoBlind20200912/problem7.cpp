#include "problem7.h"

int cost[300001] = { 0, }, visited[300001] = { 0, };
long long dp[300001][2];
unordered_map<int, vector<int>> m;

void cal(int node) {

	visited[node] = 1;

	int teammateNum = 0;

	bool isChild = false;

	for (int child : m[node]) {

		if (visited[child] == 1)
			continue;

		cal(child);

		visited[child] = 0;

		int small;
		if (dp[child][1] <= dp[child][0]) {
			teammateNum++;
			small = dp[child][1];
		}
		else
			small = dp[child][0];

		dp[node][0] += min(dp[child][0], dp[child][1]);
		dp[node][1] += min(dp[child][0], dp[child][1]);

		isChild = true;
	}

	if (isChild == false) {
		dp[node][0] = 0;
		dp[node][1] = cost[node];
		return;
	}

	// �ڽĵ��� �ּҰ����� ������ ��, ���� ������ �Ѹ� ���� ���,
	if (teammateNum == 0) {
		int small = 1000000;
		for (int child : m[node]) {
			if (visited[child] != 1 && dp[child][1] - dp[child][0] < small)
				small = dp[child][1] - dp[child][0];
		}

		dp[node][0] += small;
	}

	dp[node][1] += cost[node];

	cout << node << " " << dp[node][0] << " " << dp[node][1] << endl;
}

int solution(vector<int> sales, vector<vector<int>> links) {
 
    // sales�� ũ�� : ��� ��. => 2 �̻� 300000 ���� (30��)
    // �� sales ������ ũ�� : �Ϸ� ��� �����. => 0 �̻� 10000 ����.
    // links�� �� ���Ҵ� index 0�� �����ȣ, index1�� ������ȣ.

    int answer = 0;
    
	// ������ cost�迭 �ʱ�ȭ.
	for (int i = 1; i <= sales.size(); i++) {
		cost[i] = sales[i - 1];
	}
	
	// tree map ����.
	for (auto link : links) {
		m[link[0]].push_back(link[1]);
		m[link[1]].push_back(link[0]);
	}

	// CEO���� ��� ����.
	cal(1);

	answer = dp[1][0] < dp[1][1] ? dp[1][0] : dp[1][1];

    return answer;
}

namespace problem7 {

    void execute() {

		vector<int> sales(10,0);
		vector<vector<int>> links;

		sales[0] = 14; sales[1] = 17; sales[2] = 15;
		sales[3] = 18; sales[4] = 19; sales[5] = 14;
		sales[6] = 13; sales[7] = 16; sales[8] = 28;
		sales[9] = 17;

		vector<int> link(2,0);
		link[0] = 10; link[1] = 8;
		links.push_back(link);
		link[0] = 1; link[1] = 9;
		links.push_back(link);
		link[0] = 9; link[1] = 7;
		links.push_back(link);
		link[0] = 5; link[1] = 4;
		links.push_back(link);
		link[0] = 1; link[1] = 5;
		links.push_back(link);
		link[0] = 5; link[1] = 10;
		links.push_back(link);
		link[0] = 10; link[1] = 6;
		links.push_back(link);
		link[0] = 1; link[1] = 3;
		links.push_back(link);
		link[0] = 10; link[1] = 2;
		links.push_back(link);

		cout << solution(sales, links) << endl;
    }
}