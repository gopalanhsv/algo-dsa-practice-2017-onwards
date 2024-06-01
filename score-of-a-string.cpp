// n => s.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    scoreOfString(string s) {
        int score = 0;
        // Iterate over the string sequentially from L->R
        for (auto i = 1; i < s.size(); ++i) {
            // Compute the ascii diff between current and preceeding char
            // and add it up to the score
            score += abs(int(s[i] - s[i - 1]));
        }
        return score;
    }
};
