class Solution {
public:
    vector<string>
    summaryRanges(vector<int>& nums) {
    
        vector<string> outV;
        // Empty input array
        if (nums.empty()) {
            return outV;
        }
        
        int n = nums.size();
        // Single element input array
        if (n < 2) {
            outV.emplace_back(to_string(nums[0]));
            return outV;
        }
        
        // Elements from 0 to n - 1
        int i = 0;
        while (i < n) {
            // Compare current and previous elems and build the range
            // based on difference between them
            auto j = i + 1;
            if (j < n) {
                // Compare adjacent elements and dont stop as long as
                // difference between them is 1
                // NOTE :- Remember to do the long typecast to consider
                // huge vals of nums
                while (j < n && (long)nums[j] - (long)nums[j - 1] == 1) {
                    ++j;
                }
                // Either j = n or j is s.t. its difference from previous
                // element is more than 1
                // So range till j - 1 is fine
                j = j - 1;
            } else {
                j = i;
            }
            
            // Construct range from i to j
            if (i == j) {
                outV.emplace_back(to_string(nums[i]));
            } else {
                outV.emplace_back(
                    to_string(nums[i]) + "->" + to_string(nums[j]));
            }
            
            // Advance to next element
            i = j + 1;
        }
        
        return outV;
    }
};
