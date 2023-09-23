// Time complexity : O(nums.size())
// Space complexity : O(nums.size())
class Solution {
public:
    int
    destroyTargets(vector<int>& nums, int space) {
        // s => 'space'
        // Say A is any number in 'nums' array
        // and A = qs + r, q => quotient (any integer number) and r => remainder when A is divided by 's', 
        // Selecting A as m/c seed allows destruction of all numbers in the array with value
        // A + c * s, where c > 0 and +ve integer
        // i.e A + s, A + 2s, A + 3s, .....and so on 
        // = qs + r + s, qs + r + 2s, qs + r + 3s, qs + r + 4s, ... and so on
        // = r + (q + 1)s, r + (q + 2)s, r + (q + 2)s, r + (q + 4)s, .... and so on
        // Since 'q' is an integer, the above sequence reduces to numbers which have
        // the same remainder 'r' when divided by 's'
        // => Selecting a number 'A' as seed allows destruction of all numbers which
        // have the same remainder as A % s.
        // => Group together all numbers with the same remainder when divided by 's' AND
        // select the min number possible as m/c seed to destroy all numbers with same
        // remainder 
        
        // Build a table of all possible 'remainders' mapped to their 'frequency/occurence count'
        // and 'remainder' mapped to min number whose remainder it is
        unordered_map<int, int> remainderToFreqCntTbl;
        unordered_map<int, int> remainderToMinNumTbl;
        for (auto & num : nums) {
            auto remainder = num % space;
            remainderToFreqCntTbl[remainder]++;
            // Update the min number for computed 'remainder'
            auto it = remainderToMinNumTbl.find(remainder);
            if (it == remainderToMinNumTbl.end()) {
                remainderToMinNumTbl[remainder] = num;
            } else {
                remainderToMinNumTbl[remainder] = min(it->second, num);
            }
        }
        
        // Determine the min number whose remainder has the max occurence count
        int seed = numeric_limits<int>::max();
        int maxDestroyedTargetsSeenSoFar = 0;
        for (auto & ent : remainderToFreqCntTbl) {
            auto & remainder = ent.first;
            auto & nDestroyedTargets = ent.second;
            if (nDestroyedTargets > maxDestroyedTargetsSeenSoFar) {
                // Number with current remainder as seed destroys max targets
                seed = remainderToMinNumTbl[remainder];
                maxDestroyedTargetsSeenSoFar = nDestroyedTargets;
            } else if (nDestroyedTargets == maxDestroyedTargetsSeenSoFar) {
                // Number with current remainder as seed destroys max targets
                // Select the min number seen so for with current remainder
                seed = min(seed, remainderToMinNumTbl[remainder]);
            }
        }
        
        return seed;
    }
};
