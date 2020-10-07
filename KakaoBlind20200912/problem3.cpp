#include "problem3.h"

namespace problem3 {

	vector<int> solution(vector<string> info, vector<string> query) {

		// 각 항목의 조합에 대한 index 값을 저장한 배열.
		int dataTree[3][2][2][2];

		int index = 0;

		for (int a = 0; a < 3; a++)
			for (int b = 0; b < 2; b++)
				for (int c = 0; c < 2; c++)
					for (int d = 0; d < 2; d++) {
						dataTree[a][b][c][d] = index;
						index++;
					}

		vector<map<int, int>> datas(24);

		map<string, int> lm, wm, tm, fm;

		lm["cpp"] = 0;
		lm["java"] = 1;
		lm["python"] = 2;

		wm["backend"] = 0;
		wm["frontend"] = 1;

		tm["junior"] = 0;
		tm["senior"] = 1;

		fm["chicken"] = 0;
		fm["pizza"] = 1;

		vector<int> answer;

		// data map 생성.
		for (string str : info) {

			// 언어
			string l = str.substr(0, str.find(" "));

			// 직군
			str = str.substr(str.find(" ") + 1);
			string w = str.substr(0, str.find(" "));

			// 경력
			str = str.substr(str.find(" ") + 1);
			string t = str.substr(0, str.find(" "));

			// 음식
			str = str.substr(str.find(" ") + 1);
			string f = str.substr(0, str.find(" "));

			int score = stoi(str.substr(str.find(" ") + 1));

			datas[dataTree[lm[l]][wm[w]][tm[t]][fm[f]]][score] = 1;
		}

		for (string str : query) {

			// 언어
			string l = str.substr(0, str.find(" "));

			// 직군
			str = str.substr(str.find(" "));
			str = str.substr(5);
			string w = str.substr(0, str.find(" "));

			// 경력
			str = str.substr(str.find(" "));
			str = str.substr(5);
			string t = str.substr(0, str.find(" "));

			// 음식
			str = str.substr(str.find(" "));
			str = str.substr(5);
			string f = str.substr(0, str.find(" "));

			int queryScore = stoi(str.substr(str.find(" ")));

			int trueNum = 0; // query 조건에 맞는 총 데이터 수

			for (int a = 0; a < 3; a++)
				for (int b = 0; b < 2; b++)
					for (int c = 0; c < 2; c++)
						for (int d = 0; d < 2; d++) {

							if ((l == "-" || lm[l] == a)
								&& (w == "-" || wm[w] == b)
								&& (t == "-" || tm[t] == c)
								&& (f == "-" || fm[f] == d)) {
								// query 조건에 맞는 리스트.
								int dataIndex = 0;
								map<int, int> dataList = datas[dataTree[a][b][c][d]];
								for (auto scoreData : dataList) {
									if (scoreData.first >= queryScore) {
										trueNum += dataList.size() - dataIndex;
										break;
									}
									dataIndex++;
								}
							}
						}

			answer.push_back(trueNum);
		}

		return answer;
	}

	void execute() {

		vector<string> v, q;

		v.push_back("java backend junior pizza 150");
		v.push_back("python frontend senior chicken 210");
		v.push_back("python frontend senior chicken 150");
		v.push_back("cpp backend senior pizza 260");
		v.push_back("java backend junior chicken 80");
		v.push_back("python backend senior chicken 50");

		q.push_back("java and backend and junior and pizza 100");
		q.push_back("python and frontend and senior and chicken 200");
		q.push_back("cpp and - and senior and pizza 250");
		q.push_back("- and backend and senior and - 150");
		q.push_back("- and - and - and chicken 100");
		q.push_back("- and - and - and - 150");

		vector<int> result = solution(v, q);

		for (auto a : result)
			cout << a << " ";
		cout << endl;
	}
}