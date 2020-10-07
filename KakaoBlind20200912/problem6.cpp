#include "problem6.h"

namespace problem6 {

    int dr[4] = { -1,1,0,0 };
    int dc[4] = { 0,0,-1,1 };

    // 해당 위치가 벽인지 확인하는 함수
    bool isBlock(int r, int c) {
        return (r < 0 || r > 3 || c < 0 || c > 3);
    }

    int solution(vector<vector<int>> board, int r, int c) {

        // board 순회하여 각 카드의 좌표 데이터 map 생성.
        // 순회하면서 카드 번호 vector로 생성.
        // 카드 번호를 담은 vector sort 후 permutation.

        int answer = 1000000;

        unordered_map<int, vector<pair<int, int>>> posMap;
        vector<int> cards;

        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {

                int cardNum = board[r][c];

                if (cardNum != 0) {
                    // 카드의 좌표 입력.
                    posMap[cardNum].push_back(make_pair<int, int>((int)r, (int)c));

                    bool isCard = false;

                    for (int card : cards) {
                        if (card == cardNum) {
                            isCard = true;
                            break;
                        }
                    }

                    // 기존 card vector에 카드 데이터가 없으면 삽입.
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

                    // 각 좌표 roadmap 생성.
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

                    // 시작점.
                    int curR = r, curC = c;
                    vector<vector<int>> tempBoard = board;

                    // 이전에 카드를 오픈했는지에 대한 Flag.
                    bool isOpen = false;
                    // 이전에 오픈한 카드의 좌표
                    pair<int, int> openingCard;
                    // 현재 구하고 있는 카드 오픈 순서에 대한 비용.
                    int roadCost = 0;

                    // DFS 사용해서 차례대로 방문하여 최소비용 계산.
                    while (!roadQueue.empty()) {

                        pair<int, int> nextPos = roadQueue.front();
                        roadQueue.pop();

                        // 각 좌표의 최소비용값 초기화.
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

                            // data의 위치에서 갈 수 있는 모든 위치 조건 확인 후 탐색.
                            for (int dist = 0; dist < 4; dist++) {

                                int nr = data.first + dr[dist];
                                int nc = data.second + dc[dist];

                                if (isBlock(nr, nc) == false
                                    && visited[nr][nc] > visited[data.first][data.second] + 1) {
                                    // 조건이 맞다면 비용 갱신 후 탐색.
                                    visited[nr][nc] = visited[data.first][data.second] + 1;
                                    st.push(make_pair<int, int>((int)nr, (int)nc));
                                    isNext = true;
                                    break;
                                }

                                int ctrl_nr = data.first;
                                int ctrl_nc = data.second;

                                // ctrl + 방향키
                                for (int nd = 0; nd < 4; nd++) {

                                    // 다음 위치에 카드가 있거나 block일 경우
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
                                    // 조건이 맞다면 비용 갱신 후 탐색.
                                    visited[ctrl_nr][ctrl_nc] = visited[data.first][data.second] + 1;
                                    st.push(make_pair<int, int>((int)ctrl_nr, (int)ctrl_nc));
                                    isNext = true;
                                    break;
                                }
                            }

                            if (isNext == false)
                                st.pop();
                        }

                        // 경로탐색이 끝나면 다음 위치의 최소비용이 구해져 있다.
                        // 경로의 최소비용을 현재 카드방문 순서의 비용값에 더하고 Enter 값까지 +1 해준다.
                        // flase -> 아무것도 선택 안한 상태이므로 Enter를 눌러 카드 오픈.
                        // true -> 하나 오픈한 상태이므로 Enter 눌러 두번째 카드 오픈하고 카드 두개 없애기.

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

                    // 최소비용 갱신.
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