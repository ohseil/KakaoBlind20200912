#include "problem6.h"

namespace problem6 {

    int dr[4] = { -1,1,0,0 };
    int dc[4] = { 0,0,-1,1 };

    // �ش� ��ġ�� ������ Ȯ���ϴ� �Լ�
    bool isBlock(int r, int c) {
        return (r < 0 || r > 3 || c < 0 || c > 3);
    }

    int solution(vector<vector<int>> board, int r, int c) {

        // board ��ȸ�Ͽ� �� ī���� ��ǥ ������ map ����.
        // ��ȸ�ϸ鼭 ī�� ��ȣ vector�� ����.
        // ī�� ��ȣ�� ���� vector sort �� permutation.

        int answer = 1000000;

        unordered_map<int, vector<pair<int, int>>> posMap;
        vector<int> cards;

        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {

                int cardNum = board[r][c];

                if (cardNum != 0) {
                    // ī���� ��ǥ �Է�.
                    posMap[cardNum].push_back(make_pair<int, int>((int)r, (int)c));

                    bool isCard = false;

                    for (int card : cards) {
                        if (card == cardNum) {
                            isCard = true;
                            break;
                        }
                    }

                    // ���� card vector�� ī�� �����Ͱ� ������ ����.
                    if (isCard == false)
                        cards.push_back(cardNum);
                }
            }
        }

        sort(cards.begin(), cards.end());

        do {

            vector<int> per(cards.size(), 0);

            for (int p = 0; p <= per.size(); p++) {

                for (int p1 = per.size() - 1; p1 > per.size() - 1 - p; p1--)
                    per[p1] = 1;

                do {

                    queue<pair<int, int>> roadQueue;

                    // �� ��ǥ roadmap ����.
                    for (int rm = 0; rm < per.size(); rm++) {

                        vector<pair<int, int>> cardsPos = posMap[cards[rm]];

                        if (per[rm] == 0) {
                            roadQueue.push(make_pair<int, int>((int)cardsPos[0].first, (int)cardsPos[0].second));
                            roadQueue.push(make_pair<int, int>((int)cardsPos[1].first, (int)cardsPos[1].second));
                        }
                        else {
                            roadQueue.push(make_pair<int, int>((int)cardsPos[1].first, (int)cardsPos[1].second));
                            roadQueue.push(make_pair<int, int>((int)cardsPos[0].first, (int)cardsPos[0].second));
                        }
                    }

                    // ������.
                    int curR = r, curC = c;
                    vector<vector<int>> tempBoard = board;

                    // ������ ī�带 �����ߴ����� ���� Flag.
                    bool isOpen = false;
                    // ������ ������ ī���� ��ǥ
                    pair<int, int> openingCard;
                    // ���� ���ϰ� �ִ� ī�� ���� ������ ���� ���.
                    int roadCost = 0;

                    // DFS ����ؼ� ���ʴ�� �湮�Ͽ� �ּҺ�� ���.
                    while (!roadQueue.empty()) {

                        pair<int, int> nextPos = roadQueue.front();
                        roadQueue.pop();

                        // �� ��ǥ�� �ּҺ�밪 �ʱ�ȭ.
                        int visited[4][4];
                        for (int i = 0; i < 4; i++)
                            for (int j = 0; j < 4; j++)
                                visited[i][j] = 1000000;

                        stack<pair<int, int>> st;
                        st.push(make_pair<int, int>((int)curR, (int)curC));
                        visited[curR][curC] = 0;

                        while (!st.empty()) {

                            pair<int, int> data = st.top();

                            if (data.first == nextPos.first && data.second == nextPos.second) {
                                st.pop();
                                continue;
                            }

                            bool isNext = false;

                            // data�� ��ġ���� �� �� �ִ� ��� ��ġ ���� Ȯ�� �� Ž��.
                            for (int dist = 0; dist < 4; dist++) {

                                int nr = data.first + dr[dist];
                                int nc = data.second + dc[dist];

                                if (isBlock(nr, nc) == false
                                    && visited[nr][nc] > visited[data.first][data.second] + 1) {
                                    // ������ �´ٸ� ��� ���� �� Ž��.
                                    visited[nr][nc] = visited[data.first][data.second] + 1;
                                    st.push(make_pair<int, int>((int)nr, (int)nc));
                                    isNext = true;
                                    break;
                                }

                                int ctrl_nr = data.first;
                                int ctrl_nc = data.second;

                                // ctrl + ����Ű
                                for (int nd = 0; nd < 4; nd++) {

                                    // ���� ��ġ�� ī�尡 �ְų� block�� ���
                                    if (isBlock(ctrl_nr + dr[dist], ctrl_nc + dc[dist]) == true) {
                                        break;
                                    }

                                    if (tempBoard[ctrl_nr + dr[dist]][ctrl_nc + dc[dist]] != 0) {
                                        ctrl_nr += dr[dist];
                                        ctrl_nc += dc[dist];
                                        break;
                                    }

                                    ctrl_nr += dr[dist];
                                    ctrl_nc += dc[dist];
                                }

                                if (visited[ctrl_nr][ctrl_nc] > visited[data.first][data.second] + 1) {
                                    // ������ �´ٸ� ��� ���� �� Ž��.
                                    visited[ctrl_nr][ctrl_nc] = visited[data.first][data.second] + 1;
                                    st.push(make_pair<int, int>((int)ctrl_nr, (int)ctrl_nc));
                                    isNext = true;
                                    break;
                                }
                            }

                            if (isNext == false)
                                st.pop();
                        }

                        // ���Ž���� ������ ���� ��ġ�� �ּҺ���� ������ �ִ�.
                        // ����� �ּҺ���� ���� ī��湮 ������ ��밪�� ���ϰ� Enter ������ +1 ���ش�.
                        // flase -> �ƹ��͵� ���� ���� �����̹Ƿ� Enter�� ���� ī�� ����.
                        // true -> �ϳ� ������ �����̹Ƿ� Enter ���� �ι�° ī�� �����ϰ� ī�� �ΰ� ���ֱ�.

                        roadCost += (visited[nextPos.first][nextPos.second] + 1);

                        if (isOpen == false) {
                            openingCard.first = nextPos.first, openingCard.second = nextPos.second;
                            isOpen = true;
                        }
                        else {
                            tempBoard[openingCard.first][openingCard.second] = 0;
                            tempBoard[nextPos.first][nextPos.second] = 0;
                            isOpen = false;
                        }

                        curR = nextPos.first; curC = nextPos.second;
                    }

                    // �ּҺ�� ����.
                    if (answer > roadCost)
                        answer = roadCost;

                } while (next_permutation(per.begin(), per.end()));
            }

        } while (next_permutation(cards.begin(), cards.end()));

        return answer;
    }

    void execute() {
        int r = 0, c = 1;
        vector<vector<int>> board;
        vector<int> v(4, 0);
        v[0] = 3; v[1] = 0; v[2] = 0; v[3] = 2;
        board.push_back(v);
        v[0] = 0; v[1] = 0; v[2] = 1; v[3] = 0;
        board.push_back(v);
        v[0] = 0; v[1] = 1; v[2] = 0; v[3] = 0;
        board.push_back(v);
        v[0] = 2; v[1] = 0; v[2] = 0; v[3] = 3;
        board.push_back(v);

        cout << solution(board, r, c) << endl;

    }
}