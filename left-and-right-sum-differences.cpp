class Solution {
public:
    vector<int>
    leftRigthDifference(vector<int>& nums) {
        
        if (nums.empty()) {
            // Base case of empty array
            return vector<int>();
        }
        
        // Sum of all array elements
        int arrSum = accumulate(nums.begin(), nums.end(), 0);
        int arrSz = nums.size();
        // Init the left and right sum
        int leftSum = 0;
        int rightSum = arrSum;
        // Output array
        vector<int> answerV(arrSz);
        // Iterate over the array elements from L->R
        for (int i = 0; i != arrSz; ++i) {
            // Update right sum for current element
            rightSum -= nums[i];
            // Update output for current index
            answerV[i] = abs(leftSum - rightSum);
            // Update left sum for next element
            leftSum += nums[i]; 
        }
        
        return answerV;
    }
};
