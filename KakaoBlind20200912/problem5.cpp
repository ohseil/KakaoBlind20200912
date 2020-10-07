#include "problem5.h"

namespace problem5 {

    // int형의 초단위 데이터 -> hh:mm:ss 단위의 문자열로 변환해주는 함수
    string SecondToTime(int second) {

        string hour = to_string(second / 3600);
        second %= 3600;
        string min = to_string(second / 60);
        string sec = to_string(second % 60);
        if (hour.length() == 1)
            hour = "0" + hour;
        if (min.length() == 1)
            min = "0" + min;
        if (sec.length() == 1)
            sec = "0" + sec;

        return hour + ":" + min + ":" + sec;
    }

    // hh:mm:hh 단위의 문자열 -> int형의 초단위 데이터로 변환해주는 함수
    int TimeToSecond(string time) {

        return stoi(time.substr(0, 2)) * 3600 + stoi(time.substr(3, 2)) * 60 + stoi(time.substr(6, 2));
    }

    string solution(string play_time, string adv_time, vector<string> logs) {

        // prefix sum 알고리즘 사용.
        // 0 <= t < 360000 영상 시간 길이의 최대 길이는 00:00:00 ~ 99:59:59

        // 0초부터 99:59:59 지점까지 값을 구한다.
        // c1 = 광고 시작시간에서의 동시 시청 수.
        // c2 = 광고 끝시간에서의 동시 시청 수.
        // sum = 현재 시간까지 광고영상을 틀었을 때의 누적 시청시간.

        // c1은 0초에서의 동시 시청자 수이고 처음 00:00:00 ~ 광고 끝시간 까지 계산하여 c2를 구한다.
        // sum의 초기값은 00:00:00 ~ 광고 끝시간 까지의 누적 시청자 수이다. (c2를 구하는 과정에서 구하기 가능)
        // c1, c2, sum을 이용해서 영상의 끝시간까지 계산하면서 최대값을 찾는다.

        string answer = "";

        int finish = TimeToSecond(play_time);
        int advTime = TimeToSecond(adv_time);

        int c1 = 0, c2 = 0, sum = 0;

        unordered_map<int, int> startTimes, finishTimes;

        // 각 시청시간의 시작 과 끝 시간을 map으로 생성.
        for (string log : logs) {
            startTimes[TimeToSecond(log.substr(0, 8))]++;
            finishTimes[TimeToSecond(log.substr(9, 8))]++;
        }

        sum = c1 = c2 = startTimes[0] - finishTimes[0];

        for (int t = 1; t <= advTime; t++) {

            if (startTimes[t] > 0) {
                string st = SecondToTime(t);
                c2 += startTimes[t];
            }
            if (finishTimes[t] > 0) {
                string ft = SecondToTime(t);
                c2 -= finishTimes[t];
            }

            sum += c2;
        }

        int longestTime = sum;
        answer = "00:00:00";

        for (int t = advTime + 1; t <= finish; t++) {

            if (startTimes[t - advTime - 1] > 0)
                c1 += startTimes[t - advTime - 1];
            if (finishTimes[t - advTime - 1] > 0)
                c1 -= finishTimes[t - advTime - 1];

            if (startTimes[t] > 0)
                c2 += startTimes[t];
            if (finishTimes[t] > 0)
                c2 -= finishTimes[t];

            sum += c2;
            sum -= c1;

            if (sum > longestTime) {
                longestTime = sum;
                answer = SecondToTime(t - advTime);
            }
        }

        return answer;
    }

    void execute() {

        string play_time = "02:03:55";
        string adv_time = "00:14:15";
        vector<string> logs;
        logs.push_back("01:20:15-01:45:14");
        logs.push_back("00:40:31-01:00:00");
        logs.push_back("00:25:50-00:48:29");
        logs.push_back("01:30:59-01:53:29");
        logs.push_back("01:37:44-02:02:30");

        cout << solution(play_time, adv_time, logs) << endl;
    }
}
