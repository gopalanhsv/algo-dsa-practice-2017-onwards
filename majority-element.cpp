// Time complexity : O(nums.size()) / O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    majorityElement(vector<int>& nums) {
        // Employing the Boyer-Moore majority vote algo here
        // (https://gregable.com/2013/10/majority-vote-algorithm-find-majority.html)
        
        // There can be a maximum of 1 majority element in an array
        
        // Scan the array from left to right.
        // If candidate is unassigned, select curent number as candidate & set its count to 1.
        // If current number is same as assigned candidate, increment candidate count by 1.
        // If current number is different from assigned candidate, decrement candidate count by 1.
        // If candidate count drops to 0, majority candidate is marked as unassigned till next
        // number in stream
        
        // Candidate count dropping to 0 => equal number of majority and other numbers seen so far
        // => vote cancels out => no majority in array prefix seen
        
        int candidate;
        int candidateCnt = 0;
        for (auto & num : nums) {
            
            if (0 == candidateCnt) {
                // Candidate unassigned. Current element selected as majority candidate
                candidate = num;
                candidateCnt = 1;
            } else {
                // Candidate already assigned
                if (num == candidate) {
                    ++candidateCnt;
                } else {
                    --candidateCnt;
                }
            }
        }
        
        return candidate;
    }
};
