#include "problem2.h"

namespace problem2 {


	vector<string> solution(vector<string> orders, vector<int> course) {

		// �� ����� �ֹ����� ��� ����� course�޴� ������ map�� ����.

		// map�� ������ ���� ū ������ map�� unordered_map���� ���.
		// ���⼭ key�� course�޴��� �����ϴ� �޴� ��, value�� �� �ٸ� ���� map.
		// ���� map�� key�� course�޴�, value�� course�޴��� �ֹ��� ����.

		// ������ map�� ��ȸ�Ͽ� course�޴����� ������ 2�� �̻��̰� ���� ���� ���� course�޴��� ������.

		vector<string> answer;

		// key : course�޴��� �����ϴ� �޴� ��
		// value : ���� map.
		// ���� map�� key : course�޴� ����
		// ���� map�� value : course�޴��� �ֹ� ����
		unordered_map<int, map<vector<char>, int>> m;

		// �� course�޴� ������ ���� �������� ���� ���� �ֹ��� ���� ������ vector.
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