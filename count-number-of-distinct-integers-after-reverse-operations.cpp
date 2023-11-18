// M => max number in nums
// n => nums.size()
// Time complexity : O(nlogM)
// Space complexity : O(n)

class Solution {
public:
    int
    countDistinctIntegers(vector<int>& nums) {
        // Build hash table of 'nums' and its reverse nums so that only distinct
        // elements are retained
        unordered_set<int> numsTbl;
        
        // Iterate over all the elements in the input array
        for (auto & num : nums) {
            // Add number and its reverse to hash table
            numsTbl.insert(num);
            auto rNum = reverseNum(num);
            numsTbl.insert(rNum);
        }
        
        // Hash table retains only distinct elements
        return numsTbl.size();
    }
    
private:
    
    inline int
    reverseNum(int num) {
        int rNum = 0;
        while (num) {
            auto d = num % 10;
            rNum = rNum * 10 + d;
            num /= 10;
        }
        return rNum;
    }
};
