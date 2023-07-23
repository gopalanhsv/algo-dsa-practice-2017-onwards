// Time complexity : O(nums.size())
// Space complexity : O(1)
class Solution {
public:
    bool
    isGood(vector<int>& nums) {
        int arrSz = nums.size();
        if (arrSz < 2) {
            return false;
        }
        // The array will be good if it contains 2 occurences of the max element
        // 'arrSz - 1' and one occurence of each of the elements in the range
        // [1, arrSz - 2]
        int allSingleOccurrenceElemXor = 0;
        int maxElemCnt = 0;
        int maxElem = arrSz - 1;
        // Iterate over the array elements
        for (auto & num : nums) {
            if ((num > maxElem) || (num < 1)) {
                // Num beyond range => array is not good
                return false;
            } else if (num == maxElem) {
                ++maxElemCnt;
            } else {
                allSingleOccurrenceElemXor ^= num;
            }
        }
        // Compute the expected XOR of all single occurence elements i.e all in range [1, arrSz - 2] 
        int expectedSingleOccurenceElemXor = 0;
        for (int i = 1; i <= arrSz - 2; ++i) {
            expectedSingleOccurenceElemXor ^= i;
        }

        // Check for array goodness
        return (maxElemCnt == 2) && (allSingleOccurrenceElemXor == expectedSingleOccurenceElemXor);
    }
};
