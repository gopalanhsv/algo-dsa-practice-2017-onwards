// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(n)
class Solution {
public:
    int
    unequalTriplets(vector<int>& nums) {
        // Build frequency count table for each
        // element of the array
        unordered_map<int, int> elemFreqTbl;
        for (auto & e : nums) {
            elemFreqTbl[e]++;
        }
        
        // Triplets can be formed with 3 distinct elements
        // Iterate over the distinct array elements using frequency count table
        auto nTriplets = 0;
        auto nArrElems = nums.size();
        auto nElemsSeenEarlier = 0;
        for (auto & [currElem, currElemFreqCnt] : elemFreqTbl) {
            // Current array element 'currElem' with an occurrence count 'currElemFreqCnt'
            // forms triplets s.t. 
            // all of the elements (distinct from current) encountered earlier will be the 1st number
            // 'currElem' is the 2nd number
            // all of the elements (distinct from current) yet to be encountered will be the 3rd number
            auto nElemsYetToBeSeen = nArrElems - currElemFreqCnt - nElemsSeenEarlier;
            nTriplets += (nElemsSeenEarlier * currElemFreqCnt * nElemsYetToBeSeen);
            nElemsSeenEarlier += currElemFreqCnt;
        }

        return nTriplets;
    }
};
