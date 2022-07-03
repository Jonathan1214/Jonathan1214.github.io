class Solution {
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        vector<vector<int>> ret(m, vector<int>(n, -1));
        int state = 0;
        int r = 0;
        int c = 0;
        ret[r][c] = head->val;
        head = head->next;
        while (head != nullptr) {
            if (state == 0) {
                if (c == n - 1 || ret[r][c+1] > -1) {
                    state = 1;
                    r++;
                } else {
                    c++;
                }
            } else if (state == 1) {
                if (r == m - 1 || ret[r+1][c] > -1) {
                    state = 2;
                    c--;
                } else {
                    r++;
                }
            } else if (state == 2) {
                if (c == 0 || ret[r][c-1] > -1) {
                    state = 3;
                    r--;
                } else {
                    c--;
                }
            } else {
                if (r == 0 || ret[r-1][c] > -1) {
                    state = 0;
                    c++;
                } else {
                    r--;
                }
            }
            ret[r][c] = head->val;
            head = head->next;
        }
        return ret;
    }
};