// Time complexity : O(1)
// Space complexity : O(1)

class Solution {
public:
    int
    findNonMinOrMax(vector<int>& nums) {
        if (nums.size() <= 2) {
            // Base case of arry not having any elements other than max & min
            return -1;
        }
        
        // Array has at least 3 members and as per input constraints all numbers
        // are distinct. This implies that the array has a single maximum and a
        // single minimum => If the 1st three elements are selected from array,
        // we have following 3 cases:-
        // (1) one element can be maximum, another minimum and the last element neither
        // (2) one element can be maximum, the remaining two elements neither
        // (3) one element can be minimum, the remaining two elements neither
        // From the above, since all elements are distinct -- the element in the
        // 3 element subarray which is the mid element (neither max nor min) would
        // be the neither element
        
        // Examine the 1st 3 the elements of the array
        int subArrMin = min(nums[0], min(nums[1], nums[2]));
        int subArrMax = max(nums[0], max(nums[1], nums[2]));
        // Note that below loop sees only the first 3 elements
        for (auto num : nums) {
            if (num < subArrMax && num > subArrMin) {
                // Mid element in nums[0, 2] is neither element 
                return num;
            }
        }
        
        // Oops : Error
        return -1;
    }
};
