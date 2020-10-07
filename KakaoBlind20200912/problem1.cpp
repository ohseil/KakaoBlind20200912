#include "problem1.h"

namespace problem1 {

    // 문자 지우기.
    string eraseData(string str, map<int, int> m) {

        string result = "";

        for (int i = 0; i < str.length(); i++) {

            if (m[i] != 1)
                result += str[i];
        }
        return result;
    }

    string solution(string new_id) {

        // 루틴 한번 돌면서
        // 대문자는 소문자로 변경하고,
        // 문자, ., -, _, 숫자를 제외한 문자들의 index를 리스팅한다.
        // .가 연속 2번 나올때도 마지막 .의 index를 리스팅한다.
        // 이때 처음이나 끝에 마침표가 있는 것도 리스팅한다.

        // 리스팅한 index를 이용해서 제거한 결과의 문자열 저장.

        // 저장한 문자열이 빈 문자열이라면 "a" 붙이기.
        // 문자열의 길이가 16 이상이라면 처음 15개 빼고 지운다.
        // 이 때, .가 마지막에 온다면 지운다.

        // 완료 후 길이가 2 이하라면 마지막 문자를 길이가 3 될때까지 붙인다.

        string answer = "";

        map<int, int> eraseList;

        char beforeChar = NULL;

        for (int i = 0; i < new_id.length(); i++) {
            // 65 ~ 90 대문자
            // 97 ~ 122 소문자
            // 48 ~ 57 숫자
            // . => 46, - => 45 _ => 95
            int intData = new_id[i];
            if ((97 <= intData && intData <= 122)
                || (48 <= intData && intData <= 57)) {
                // 소문자 or 숫자 (적합문자)
            }
            else if (65 <= intData && intData <= 90) {
                // 대문자이므로 소문자로 변경.
                new_id[i] = (char)(intData + 32);
            }
            else if (intData == 46 || intData == 45 || intData == 95) {
                // . 이거나 - 이거나 _
            }
            else {
                // 부적합한 문자이므로 제거대상
                eraseList[i] = 1;
            }
        }

        answer = eraseData(new_id, eraseList);

        eraseList.clear();

        for (int i = 0; i < answer.length(); i++) {
            if ((int)answer[i] == 46) {
                // 마침표
                if (beforeChar == '.')
                    eraseList[i] = 1;
            }

            beforeChar = answer[i];
        }

        answer = eraseData(answer, eraseList);

        eraseList.clear();

        // 끝과 마지막에 . 라면 지우기
        if (answer[0] == '.')
            eraseList[0] = 1;
        if (answer[answer.length() - 1] == '.')
            eraseList[answer.length() - 1] = 1;

        answer = eraseData(answer, eraseList);

        if (answer.length() == 0) {
            // 빈 문자열이라면 문자 a 붙이기.
            answer += "a";
        }
        else if (answer.length() >= 16) {
            // 문자열의 길이가 16 이상이라면 처음 15개의 문자열만 저장.
            answer = answer.substr(0, 15);
        }

        if (answer[answer.length() - 1] == '.') {
            // 가공한 문자열의 마지막 문자가 . 라면 지우기.
            answer = answer.substr(0, 14);
        }

        if (answer.length() < 3) {
            // 가공한 문자열의 길이가 3 미만이라면
            // 마지막 문자를 길이가 3 될때까지 붙인다.
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