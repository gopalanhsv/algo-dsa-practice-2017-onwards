// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    minimumIndex(vector<int>& nums) {
        auto n = nums.size();
        if (n <= 1) {
            return -1;
        }
        
        // Dominant element is x => 2 * freq[x] > n => freq[x] > n/2
        // => Dominant element is same as majority element of the array
        // Problem constraints specify presence of a dominant/majority element
        // Employ Boyer-Moore majority vote algo to determine the dominant element
        // (https://gregable.com/2013/10/majority-vote-algorithm-find-majority.html)
        // Iterate over the array from L->R
        int candidate; // Dominant element candidate
        // Tracks dominant element candidate count. If candidate count drops to 0,
        // majority candidate is marked as unassigned till next
        int candidateCnt = 0;
        for (auto & num : nums) {
            if (0 == candidateCnt) {
                // Candidate unassigned. Current element selected as majority candidate
                candidate = num;
                candidateCnt = 1;
            } else {
                // Candidate already assigned
                if (num == candidate) {
                    // Current number is same as assigned candidate, increment count by 1
                    ++candidateCnt;
                } else {
                    // Current number is different from assigned candidate, decrement count by 1
                    --candidateCnt;
                }
            }
        }

        // Splitting at index 'i' should be s.t that 'd1' - dominant element {nums[0, i]}
        // should be same as 'd2' dominant element {nums[i + 1, arrSz - 1]}.
        // For split to be feasible, 'd1' & 'd2' for both partitions should be identical
        // to majority element of array. If d1 & d2 have some value other than the majority
        // element of 'nums', count(d1) + count(d2) should exceed that of any other array
        // element making d1/d2 as the array majority element which is self contradictory.
        
        // So the above reduces to finding an index 'i' s.t majority in nums[0, i] is
        // same as in num[i + 1, arrSz - 1] and equal to array majority
        
        // Compute the frequency count of majority element
        auto & majorityElem = candidate;
        auto arrSz = nums.size();
        auto majorityCnt = 0;
        for (auto & num : nums) {
            if (num == majorityElem) {
                ++majorityCnt;
            }
        }
        
        int partitionIdx = -1;
        auto majorityCntLeftHalf = 0;
        auto majorityCntRightHalf = majorityCnt;
        for (auto i = 0; i < arrSz; ++i) {
            if (nums[i] == majorityElem) {
                ++majorityCntLeftHalf; // nums[0, i]
                --majorityCntRightHalf; // nums[i + 1, arrSz - 1]
                if ((majorityCntLeftHalf * 2 > i + 1) &&
                    (majorityCntRightHalf * 2 > arrSz - 1 - i)) {
                    partitionIdx = i;
                    break;
                }
            }
        }
        
        return partitionIdx;
    }
};
