// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    vector<int>
    findErrorNums(vector<int>& nums) {
        return findErrorNumsOnePassApproach(nums);
        //return findErrorNumsTwoPassApproach(nums);
    }

private:
    vector<int>
    findErrorNumsTwoPassApproach(vector<int>& nums) {
        // Since the array of size 'n' contains only number in [1, n]; the sorted
        // location of the number 'x' would be at index 'x - 1'
        auto n = nums.size();
        
        // Use the input array itself as a hash table for marking the presence of
        //number 'x' by negsting the number stored at its sorted location 'x - 1'
        int duplicateNum;
        int expectedNumsXor = 0;
        int actualNumsXor = 0;
        // Iterate over each number in the array
        for (auto i = 0; i < n; ++i) {
            // Get number at location 'i' and find
            // its final sorted location/hash table idx
            auto num = abs(nums[i]);
            auto sortedIdx = num - 1;
            
            if (nums[sortedIdx] < 0) {
                // Number 'num' has been seen earlier in the array
                // and is the duplicate
                duplicateNum = num;
            } else {
                // Number 'num' has not been seen earlier in the array
                // Mark its presence by using array itself as hash table
                // by negaating the number stored at its sorted location
                nums[sortedIdx] = -nums[sortedIdx];
            }
        }
        
        // All numbers present in the array will have their final
        // sorted locations marked -ve; Only the missing number
        // will not have its final sorted location marked -ve.
        int missingNum;
        for (auto i = 0; i < n; ++i) {
            
            if (nums[i] > 0) {
                // Number whose final sorted location is 'i';
                // i.e. number 'i + 1' is marked as not present.
                // Hence it is the missing number
                missingNum = i + 1;
                break;
            }
        }
        
        return vector<int>({duplicateNum, missingNum});
    }

    vector<int>
    findErrorNumsOnePassApproach(vector<int>& nums) {
        // Since the array of size 'n' contains only number in [1, n]; the sorted
        // location of the number 'x' would be at index 'x - 1'
        
        // Use the input array itself as a hash table for marking the presence of
        //number 'x' by negsting the number stored at its sorted location 'x - 1'
        
        int duplicateNum;
        int expectedNumsXor = 0;
        int actualNumsXor = 0;
        // Iterate over each number in the array
        for (auto i = 0; i != nums.size(); ++i) {
            // Get number at location 'i' and find
            // its final sorted location/hash table idx
            auto num = abs(nums[i]);
            auto sortedIdx = num - 1;
            
            if (nums[sortedIdx] < 0) {
                // Number 'num' has been seen earlier in the array
                // and is the duplicate
                duplicateNum = num;
            } else {
                // Number 'num' has not been seen earlier in the array
                // Mark its presence by using array itself as hash table
                // by negaating the number stored at its sorted location
                nums[sortedIdx] = -nums[sortedIdx];
            }
            
            expectedNumsXor ^= (i + 1);
            actualNumsXor ^= num;
        }

        auto missingAndDupXor = expectedNumsXor ^ actualNumsXor;
        auto missingNum = missingAndDupXor ^ duplicateNum;
        
        return vector<int>({duplicateNum, missingNum});
    }
    
};
