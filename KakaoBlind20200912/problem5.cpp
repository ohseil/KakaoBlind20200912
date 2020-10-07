#include "problem5.h"

namespace problem5 {

    // int���� �ʴ��� ������ -> hh:mm:ss ������ ���ڿ��� ��ȯ���ִ� �Լ�
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

    // hh:mm:hh ������ ���ڿ� -> int���� �ʴ��� �����ͷ� ��ȯ���ִ� �Լ�
    int TimeToSecond(string time) {

        return stoi(time.substr(0, 2)) * 3600 + stoi(time.substr(3, 2)) * 60 + stoi(time.substr(6, 2));
    }

    string solution(string play_time, string adv_time, vector<string> logs) {

        // prefix sum �˰��� ���.
        // 0 <= t < 360000 ���� �ð� ������ �ִ� ���̴� 00:00:00 ~ 99:59:59

        // 0�ʺ��� 99:59:59 �������� ���� ���Ѵ�.
        // c1 = ���� ���۽ð������� ���� ��û ��.
        // c2 = ���� ���ð������� ���� ��û ��.
        // sum = ���� �ð����� �������� Ʋ���� ���� ���� ��û�ð�.

        // c1�� 0�ʿ����� ���� ��û�� ���̰� ó�� 00:00:00 ~ ���� ���ð� ���� ����Ͽ� c2�� ���Ѵ�.
        // sum�� �ʱⰪ�� 00:00:00 ~ ���� ���ð� ������ ���� ��û�� ���̴�. (c2�� ���ϴ� �������� ���ϱ� ����)
        // c1, c2, sum�� �̿��ؼ� ������ ���ð����� ����ϸ鼭 �ִ밪�� ã�´�.

        string answer = "";

        int finish = TimeToSecond(play_time);
        int advTime = TimeToSecond(adv_time);

        int c1 = 0, c2 = 0, sum = 0;

        unordered_map<int, int> startTimes, finishTimes;

        // �� ��û�ð��� ���� �� �� �ð��� map���� ����.
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
