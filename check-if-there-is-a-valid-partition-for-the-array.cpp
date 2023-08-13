// Time complexity : O(nums.size())
// Space complexity : O(1)

class Solution {
public:
    bool
    validPartition(vector<int>& nums) {
        int arrSz = nums.size();
        if (arrSz < 2) {
            // Array having l.t 2 elems => partitioning impossible
            return false;
        }
        
        // Problem approach is akin to iterative computation for factorial
        
        // i => current position within the array
        // Indicates that subarray [0, i] is a valid partition when 'true'
        bool validPartitionTill_i = false;
        // Indicates that subarray [0, i - 1] (ending 1 position to left)
        // is a valid partition when 'true'
        bool validPartitionTill_i_1 = false;
        // Indicates that subarray [0, i - 2] (ending 2 positions to left)
        // is a valid partition when 'true'
        bool validPartitionTill_i_2 = false;
        // Indicates that subarray [0, i - 3] (ending 3 positions to left)
        // is a valid partition when 'true'
        bool validPartitionTill_i_3 = false;
        
        // Initializing partition flags for subarray [0, 1]
        // Check for condition#1
        validPartitionTill_i = (nums[1] == nums[0]);
        
        // Array of size 3 +
        // Compute partition flags for subarray [0, 2]
        if (arrSz >= 3) {
            // Subarray [0, 1] ends 1 position to left
            validPartitionTill_i_1 = validPartitionTill_i;
            // Compute partition flag for subarray [0, 2]
            validPartitionTill_i = false;
            if (nums[1] == nums[2]) {
                // Updated to condition # 2 : 3 equal elements
                validPartitionTill_i = validPartitionTill_i_1;
            } else if ((nums[1] == nums[0] + 1) && (nums[2] == nums[1] + 1)) {
                // Condition # 3
                validPartitionTill_i = true;
            } 
        }
        
        // Compute the valid partition via iterative DP for the entire
        // array incrementally for array of size 4+
        for (auto subArrSz = 4; subArrSz <= arrSz; ++subArrSz) {
            // Final index for given subarray size
            auto i = subArrSz - 1;

            // Determine the valid partitioning possibility for subarray [0, i] 
            
            // Adjust flags such that current flags get shifted 1 position to left
            // as the subarray end index has moved ahead by one step
            validPartitionTill_i_3 = validPartitionTill_i_2;
            validPartitionTill_i_2 = validPartitionTill_i_1;
            validPartitionTill_i_1 = validPartitionTill_i;
            validPartitionTill_i = false;
            
            if ((nums[i] == nums[i - 1]) && validPartitionTill_i_2) {
                // Subarray nums[i - 1, i] (condition # 1) & subarray [0, i - 2] allow
                // valid partitions => subarray[0, i] allows valid partition
                validPartitionTill_i = true;
            } else if (validPartitionTill_i_3) {
    
                if ((nums[i] == nums[i - 1]) && (nums[i - 1] == nums[i - 2])) {
                    // Subarray nums[i - 2, i] (condition # 2) & subarray [0, i - 2] allow
                    // valid partitions => subarray[0, i] allows valid partition
                    validPartitionTill_i = true;
                } else if ((nums[i] == nums[i - 1] + 1) && (nums[i - 1] == nums[i - 2] + 1)) {
                    // Subarray nums[i - 2, i] (condition # 3) & subarray [0, i - 2] allow
                    // valid partitions => subarray[0, i] allows valid partition
                    validPartitionTill_i = true;
                }
            }
        }
        
        return validPartitionTill_i;
    }
};
