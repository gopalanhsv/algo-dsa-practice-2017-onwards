// n => happinss.size()
// Time complexity : O(nlogn)
// Space complexity : O(logn)

class Solution {
public:
    long long
    maximumHappinessSum(vector<int>& happiness, int k) {
        // To maximize the sum of happiness values, adopt the greedy approach
        // of maximizing the sum during each child selection step, i.e. by always
        // selecting the child with the maximum happiness value from amongst
        // the remainder selection pool
        // => Select 'k' children with the max initial happiness values from all available
        // and decrement the initial happiness value of each selected child to account
        // for later selection(i.e child not being selected first)
        
        // Sort the children non-decreasing order of their happiness values
        sort(happiness.begin(), happiness.end(), greater<int>());
        
        auto nChildren = happiness.size();
        long long maxSum = 0;
        // Select 'k' children in descending order of their happiness values
        for (auto i = 0; i < k && i < nChildren; ++i) {
            // 'i' children would have been selected prior to current child 'i'
            // Adjust happiness value appropriately
            long long netHappinessVal = max(0, happiness[i] - i);
            if (netHappinessVal <= 0) {
                // All selected children post the curent child will have
                // a net happiness of '0'
                break;
            }
            
            maxSum += netHappinessVal;
        }
        
        return maxSum;
    }
};
