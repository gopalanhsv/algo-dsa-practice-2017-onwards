// q => queries.size()
// Time complexity : O(q)
// Space complexity : O(1)
class Solution {
public:
    vector<int>
    elementInNums(vector<int>& nums, vector<vector<int>>& queries) {
        auto n = nums.size();

        // t = 0, array size is n and modifiedNums[i] = nums[i]
        // t = 1, modified array size is n - 1 and modifiedNums[i] = nums[i + 1]
        // t = 2, modified array size is n - 2 and modifiedNums[i] = nums[i + 2]
        // t = 3, modified array size is n - 3 and modifiedNums[i] = nums[i + 3]
        //......................................................................  
        // t = x, modified array size is n - x and modifiedNums[i] = nums[i + x]  
        //......................................................................
        // t = n, modified array size is n - n = 0 
        // t = n + 1, modified array size is 1 and modifiedNums[i] = nums[i]
        // t = n + 2, modified array size is 2 and modifiedNums[i] = nums[i]
        // t = n + 3, modified array size is 3 and modifiedNums[i] = nums[i]
        //......................................................................  
        // t = n + x, modified array size is x and modifiedNums[i] = nums[i]  
        //......................................................................
        // t = n + n, modified array size is n and modifiedNums[i] = nums[i] 
        // And the above cycle repeats
        // Cycle length is '2n'
        
        // The above reduces to :
        // T = time % 2n
        // For  T >= 0 & T <= n, value at index 'i' = nums[i + T] if i + T < n, else -1
        // For  T > n & T <= 2n - 1, value at index 'i' = nums[i] if i < T - n, else -1
        
        auto cycleTime = 2 * n;
        auto nQueries = queries.size();
        vector<int> outV(nQueries, -1);
        // Iterate over each query
        for (auto i = 0; i != nQueries; ++i) {
            auto & qTime = queries[i][0];
            auto & qIdx = queries[i][1];
            
            // T
            auto adjustedTime = qTime % cycleTime;
            if (adjustedTime <= n) {
                // T >= 0 & T <= n, value at index 'i' = nums[i + T] if i + T < n, else -1
                if (qIdx + adjustedTime < n) {
                    outV[i] = nums[qIdx + adjustedTime];
                }
            } else {
                // T > n & T <= 2n - 1, value at index 'i' = nums[i] if i < T - n, else -1
                if (qIdx < adjustedTime - n) {
                    outV[i] = nums[qIdx];
                }
            }
        }
        
        return outV;
    }
};
