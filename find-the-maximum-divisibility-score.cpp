// Time complexity : O(nums.size() x divisors.size())
// Space complexity : O(1)

class Solution {
public:
    int
    maxDivScore(vector<int>& nums, vector<int>& divisors) {
        // Tracks min valued divisor with max divisibility score
        int maxScoreDivisor = divisors[0];
        // Tracks max divisibility score seen so far
        int maxScoreSeenSoFar = 0;
        // Iterate over each divisor
        for (auto & div : divisors) {
            int currDivScore = 0;
            // Iterate over each number. Check if number is divisible by current divisor
            for (auto elem : nums) {
                if (0 == elem % div) {
                    // Divisor divides number
                    ++currDivScore;
                }
            }
            
            // Update the divisor with max divisibility score if required
            if (currDivScore > maxScoreSeenSoFar) {
                maxScoreSeenSoFar = currDivScore;
                maxScoreDivisor = div;
            } else if (currDivScore == maxScoreSeenSoFar) {
                maxScoreSeenSoFar = currDivScore;
                maxScoreDivisor = min(div, maxScoreDivisor);
            } 
        }
        
        return maxScoreDivisor;
    }
};
