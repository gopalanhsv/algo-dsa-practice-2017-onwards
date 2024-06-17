// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    vector<int>
    orArray(vector<int>& nums) {
        // Iterate over each element of 'nums' sequentially
        auto n = nums.size();
        vector<int> answerV(n - 1);
        for (auto i = 1; i < n; ++i) {
            // Generate the answer by ORing adjacent elems
            answerV[i - 1] = (nums[i - 1] | nums[i]);
        }
        
        return answerV;
    }
};
