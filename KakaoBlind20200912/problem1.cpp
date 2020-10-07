#include "problem1.h"

namespace problem1 {

    // ���� �����.
    string eraseData(string str, map<int, int> m) {

        string result = "";

        for (int i = 0; i < str.length(); i++) {

            if (m[i] != 1)
                result += str[i];
        }
        return result;
    }

    string solution(string new_id) {

        // ��ƾ �ѹ� ���鼭
        // �빮�ڴ� �ҹ��ڷ� �����ϰ�,
        // ����, ., -, _, ���ڸ� ������ ���ڵ��� index�� �������Ѵ�.
        // .�� ���� 2�� ���ö��� ������ .�� index�� �������Ѵ�.
        // �̶� ó���̳� ���� ��ħǥ�� �ִ� �͵� �������Ѵ�.

        // �������� index�� �̿��ؼ� ������ ����� ���ڿ� ����.

        // ������ ���ڿ��� �� ���ڿ��̶�� "a" ���̱�.
        // ���ڿ��� ���̰� 16 �̻��̶�� ó�� 15�� ���� �����.
        // �� ��, .�� �������� �´ٸ� �����.

        // �Ϸ� �� ���̰� 2 ���϶�� ������ ���ڸ� ���̰� 3 �ɶ����� ���δ�.

        string answer = "";

        map<int, int> eraseList;

        char beforeChar = NULL;

        for (int i = 0; i < new_id.length(); i++) {
            // 65 ~ 90 �빮��
            // 97 ~ 122 �ҹ���
            // 48 ~ 57 ����
            // . => 46, - => 45 _ => 95
            int intData = new_id[i];
            if ((97 <= intData && intData <= 122)
                || (48 <= intData && intData <= 57)) {
                // �ҹ��� or ���� (���չ���)
            }
            else if (65 <= intData && intData <= 90) {
                // �빮���̹Ƿ� �ҹ��ڷ� ����.
                new_id[i] = (char)(intData + 32);
            }
            else if (intData == 46 || intData == 45 || intData == 95) {
                // . �̰ų� - �̰ų� _
            }
            else {
                // �������� �����̹Ƿ� ���Ŵ��
                eraseList[i] = 1;
            }
        }

        answer = eraseData(new_id, eraseList);

        eraseList.clear();

        for (int i = 0; i < answer.length(); i++) {
            if ((int)answer[i] == 46) {
                // ��ħǥ
                if (beforeChar == '.')
                    eraseList[i] = 1;
            }

            beforeChar = answer[i];
        }

        answer = eraseData(answer, eraseList);

        eraseList.clear();

        // ���� �������� . ��� �����
        if (answer[0] == '.')
            eraseList[0] = 1;
        if (answer[answer.length() - 1] == '.')
            eraseList[answer.length() - 1] = 1;

        answer = eraseData(answer, eraseList);

        if (answer.length() == 0) {
            // �� ���ڿ��̶�� ���� a ���̱�.
            answer += "a";
        }
        else if (answer.length() >= 16) {
            // ���ڿ��� ���̰� 16 �̻��̶�� ó�� 15���� ���ڿ��� ����.
            answer = answer.substr(0, 15);
        }

        if (answer[answer.length() - 1] == '.') {
            // ������ ���ڿ��� ������ ���ڰ� . ��� �����.
            answer = answer.substr(0, 14);
        }

        if (answer.length() < 3) {
            // ������ ���ڿ��� ���̰� 3 �̸��̶��
            // ������ ���ڸ� ���̰� 3 �ɶ����� ���δ�.
            char ch = answer[answer.length() - 1];
            while (answer.length() < 3) {
                answer += ch;
            }
        }

        return answer;
    }

    void execute() {

        string str = "...!@BaT#*..y.abcdefghijklm";

        cout << solution(str) << endl;
    }
}