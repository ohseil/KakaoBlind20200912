#include "problem2.h"

namespace problem2 {


	vector<string> solution(vector<string> orders, vector<int> course) {

		// 각 사람의 주문마다 모든 경우의 course메뉴 조합을 map에 저장.

		// map의 구조는 가장 큰 범위의 map은 unordered_map으로 사용.
		// 여기서 key는 course메뉴를 구성하는 메뉴 수, value는 또 다른 하위 map.
		// 하위 map의 key는 course메뉴, value는 course메뉴를 주문한 개수.

		// 구성된 map을 순회하여 course메뉴마다 개수가 2개 이상이고 가장 많이 나온 course메뉴를 리스팅.

		vector<string> answer;

		// key : course메뉴를 구성하는 메뉴 수
		// value : 하위 map.
		// 하위 map의 key : course메뉴 조합
		// 하위 map의 value : course메뉴의 주문 개수
		unordered_map<int, map<vector<char>, int>> m;

		// 각 course메뉴 조합의 구성 개수마다 가장 많이 주문된 수를 저장할 vector.
		vector<int> courseNum(11, 0);

		for (auto order : orders) {

			for (auto c : course) {

				if (c > order.size())
					break;

				vector<int> indexV(order.length(), 0);

				for (int i = 0; i < c; i++)
					indexV[indexV.size() - 1 - i] = 1;

				do {

					vector<char> newMenu;

					for (int j = 0; j < indexV.size(); j++) {
						if (indexV[j] == 1)
							newMenu.push_back(order[j]);
					}

					sort(newMenu.begin(), newMenu.end());

					m[c][newMenu]++;

					if (courseNum[c] < m[c][newMenu])
						courseNum[c] = m[c][newMenu];

				} while (next_permutation(indexV.begin(), indexV.end()));
			}

		}

		for (auto c : course) {

			map<vector<char>, int> mList = m[c];

			for (auto menu : mList) {

				if (menu.second >= 2 && menu.second == courseNum[c]) {

					string str = "";

					for (char ch : menu.first)
						str += ch;

					answer.push_back(str);
				}
			}
		}

		sort(answer.begin(), answer.end());

		return answer;
	}

	void execute() {

		vector<string> v(7, "");
		v[0] = "ABCDE"; v[1] = "AB"; v[2] = "CD";
		v[3] = "ADE"; v[4] = "XYZ"; v[5] = "XYZ";
		v[6] = "ACD";

		vector<int> c(3, 0);
		c[0] = 2;
		c[1] = 3;
		c[2] = 5;

		vector<string> result = solution(v, c);

		for (auto a : result)
			cout << a << " ";

		cout << endl;
	}
}