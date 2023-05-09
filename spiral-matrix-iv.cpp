// nr => num matrix rows, nc => num matrix cols
// Time complexity : O(nr x nc)
// Space complexity : O(nr x nc)

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<vector<int>>
    spiralMatrix(int m, int n, ListNode* head) {

        // Output matrix (initialized with -1)
        vector<vector<int> > matrix(m, vector<int>(n, -1));
        // Boundary of the submatrix for spiral move
        // being executed at any instant
        int topRow = 0;
        int bottomRow = m - 1;
        int leftCol = 0;
        int rightCol = n - 1;

        int nCells = m * n;
        ListNode* currNode = head;
        while (currNode) {
            // Fill top row of spiral from left to right
            int r = topRow;
            int c = leftCol;
            while ((currNode) && (c <= rightCol)) {
                matrix[r][c] = currNode->val;
                currNode = currNode->next;
                ++c;
            }
            
            // Fill right col of spiral from top to bottom
            r = topRow + 1;
            c = rightCol;
            while ((currNode) && (r <= bottomRow)) {
                matrix[r][c] = currNode->val;
                currNode = currNode->next;
                ++r;
            }

            // Fill bottom row of spiral from right to left
            r = bottomRow;
            c = rightCol - 1;
            while ((currNode) && (c >= leftCol)) {
                matrix[r][c] = currNode->val;
                currNode = currNode->next;
                --c;
            }

            // Fill left col of spiral from bottom to top
            r = bottomRow - 1;
            c = leftCol;
            while ((currNode) && (r > topRow)) {
                matrix[r][c] = currNode->val;
                currNode = currNode->next;
                --r;
            }

            // Adjust boundary of submatrix for next iteration
            // spiral move
            ++topRow;
            --bottomRow;
            ++leftCol;
            --rightCol;
        }

        return matrix;
    }
};
