// Time complexity : O(nums.size())
// Space complexity : O(1)
class Solution {
public:
    int
    maximizeSum(vector<int>& nums, int k) {
        // Adopt the greedy approach of maximizing score by selecting
        // the maximum array element in each of the 'k' selection steps
        // If we selection maxVal at 'i'the step, score = score + maxVal
        // and maxVal gets replaced by maxVal + 1, which will become the
        // max element of the array
        // Adopting the greedy approach, score increases as per following AP
        // maxVal, maxVal + 1, maxVal + 2, ......., maxVal + k - 2, maxVal + k - 1
        // Score = sum of above AP terms
        int maxElem = *max_element(nums.begin(), nums.end());
        return (k * (maxElem + maxElem + k - 1)) / 2;
    }
};
