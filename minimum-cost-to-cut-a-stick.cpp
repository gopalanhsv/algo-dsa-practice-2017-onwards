// Memoization approach
// nc => number of cuts
// Time complexity : O(nc ^ 3) + O(nc x lognc)
// Space complexity : O(nc ^ 2)
class Solution {
public:
    int
    minCost(int n, vector<int>& cuts) {
        if ((n < 2) || cuts.empty()) {
            // Base case of no possible cuts
            return 0;
        }
        
        return minCostViaTopDownMemoization(n, cuts);
    }
    
private:
    
    int
    minCostViaTopDownMemoizationRec(
        int lo, int hi, vector<int>& cutsV, vector<vector<int> >& minCostTbl) {
        
        if (-1 != minCostTbl[lo][hi]) {
            // Computed earlier and stored in cache
            return minCostTbl[lo][hi];
        }
        
        // Iterate over possible cut locations sequentially in ascending
        // order over the stick segment portion [cutsV[lo], cutsV[hi]];
        // and compute the min cut cost possible for this stick segment
        int minCostOverAllCuts = numeric_limits<int>::max();
        int stickSegmentLen = cutsV[hi] - cutsV[lo];
        for (int cutIdx = lo + 1; cutIdx < hi; ++cutIdx) {
            // Exec the cut at location cutsV[cutIdx]
            // Min cost of cut at current location would be the sum of
            // the individual min cut cost for the 2 stick segments as a result
            // of the split + the current stick segment length
            int currCutCost =
                stickSegmentLen +
                minCostViaTopDownMemoizationRec(lo, cutIdx, cutsV, minCostTbl) + 
                minCostViaTopDownMemoizationRec(cutIdx, hi, cutsV, minCostTbl);
            // Update the min cost over all cuts possible for current
            // stick segment to include the current cut
            minCostOverAllCuts = min(minCostOverAllCuts, currCutCost);
        }
        
        // Update the min cost over all cuts for stick segment [cutsV[lo], cutsV[hi]]
        // in the cache
        minCostTbl[lo][hi] = minCostOverAllCuts;
        return minCostOverAllCuts;
    }    
    
    
    int
    minCostViaTopDownMemoization(int n, vector<int>& cuts) {
        // Sort the cuts in ascending order of their locations
        sort(cuts.begin(), cuts.end());
        
        // Splitting the stick at an index 'cIdx' in 'cuts', splits it into two portions
        // [0, cuts[cIdx]] and [cuts[cIdx], n], incurring a cost for the step of 'n'
        // If minCost(lo, hi) represents the minimum cost incurred in splitting portion
        // of the stick [lo, hi] using only all possible ordering of 'cuts' lying in the
        // region [lo, hi], we get minCost(lo, hi) = 
        //    (hi - lo) + 
        //    min value of minCost(lo, cuts[cIdx]) + minCost(cuts[cIdx], hi)
        //    where cuts[cIdx] represent all possible cuts in the range [lo, hi]
        // The above equation has an optimal substructure property lending itself to
        // implementation via DP.
        // Since the 'cuts' array does not have the ends of the stick
        int nCuts = cuts.size();
        
        // Since the 'cuts' array does not include the start/end
        // points of the stick, add both to the same
        vector<int> cutsV;
        cutsV.emplace_back(0);
        copy(cuts.begin(), cuts.end(), back_inserter(cutsV));
        cutsV.emplace_back(n);

        // minCostTbl[i][j] gives the min total cost amongst all possible ordering
        // of cuts in portion of stick delimited by {cutsV[i], cutsV[j]}
        vector<vector<int> > minCostTbl(nCuts + 2, vector<int>(nCuts + 2, -1));
        for (int i = 0; i < cutsV.size() - 1; ++i) {
            // No cuts possible between adjacent cut locations => cut cost is 0
            minCostTbl[i][i + 1] = 0;
        }

        //return 0;
        return minCostViaTopDownMemoizationRec(0, cutsV.size() - 1, cutsV, minCostTbl);
    }
};
