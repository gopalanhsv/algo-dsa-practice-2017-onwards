// p => commands.size()
// Time Complexity : O(p)
// Space Complexity : O(1)

class Solution {
public:
    int
    finalPositionOfSnake(int n, vector<string>& commands) {

        // Tracks the current position of snake (row, column)
        int r = 0, c = 0;
        // Iterate over each command in sequence and compute snake position
        for (auto & cmd : commands) {
            if ("LEFT" == cmd) {
                c -= 1;
            } else if ("RIGHT" == cmd) {
                c += 1;
            } else if ("DOWN" == cmd) {
                r += 1;
            } else if ("UP" == cmd) {
                r -= 1;
            } else {
                // Error
                return -1;
            }
        }
        
        // Adjust (r, c) numbering format to cell-id based numbering
        return (r * n + c);
    }
};
