// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(1)
class Solution {
public:
    int
    missingNumber(vector<int>& nums) {
        
        // Array consists of 'n' distinct elements in the closed range [0, n]
        // with a single missing number
        int n = nums.size();
        // XOR of all numbers in the range [0, n] (n is array size)
        int allNumsXor = 0;
        // XOR of all array elements
        int allArrayElemsXor = 0;
        // Iterate over each array element and XOR them. Also XOR all numbers
        // in the range [0, n]
        for (auto i = 0; i < n; ++i) {
            allArrayElemsXor ^= nums[i];
            allNumsXor ^= i;
        }
        allNumsXor ^= n;
        
        // Array elements and all elements [0, n] which are identical cancel
        // out (XOR to 0) leaving only the missing element
        return allArrayElemsXor ^ allNumsXor;
    }
};
