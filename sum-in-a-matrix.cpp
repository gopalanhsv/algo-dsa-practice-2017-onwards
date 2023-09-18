// nr => num rows, nc => num cols
// Time complexity : O(nr x (nclognc))
// Space complexity : O(lognc)
class Solution {
public:
    int
    matrixSum(vector<vector<int>>& nums) {
        // Num matrix rows/col
        int nr = nums.size();
        int nc = nums[0].size();
        
        // Sort each row in non-increasing order as this enables fast selection
        // of largest number in each row by placing them at row front
        for (auto & rowV : nums) {
            sort(rowV.begin(), rowV.end(), greater<int>());
        }
        
        // Iterate over the matrix in column major fashion, selecting the
        // max number in each row and adding it up to the total score
        int score = 0;
        for (auto c = 0; c != nc; ++c) {
            int currColMax = nums[0][c];
            for (auto r = 1; r < nr; ++r) {
                currColMax = max(currColMax, nums[r][c]);
            }
            score += currColMax;
        }
        
        return score;
    }
};
