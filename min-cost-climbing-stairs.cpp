// n=> cost.size()
// DP Iterative/Bottom Up
// Time complexity : O(n)
// Space complexity : O(1)

// DP Memoization/Top Down
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    int
    minCostClimbingStairs(vector<int>& cost) {    
        _nSteps = cost.size();
        return minCostDpIterative(cost);
        return minCostClimbingStairsMemoization(cost);
    }
    
private:
    
    int
    minCostClimbingStairsMemoization(vector<int>& cost) {   
        // memoTbl[i] is the min cost to reach top
        // of stairs from the 'i' table
        vector<int> memoTbl(_nSteps, -1);
        
        // We can start either from step 0 or step 1
        int minCostFromStep0 = minCostViaMemoization(memoTbl, 0, cost);
        int minCostFromStep1 = minCostViaMemoization(memoTbl, 1, cost);

        return min(minCostFromStep0, minCostFromStep1);
    }
    
    // Minimum cost to reach stairs top from 'step'th step
    int
    minCostViaMemoization(vector<int>& memoTbl, int step, vector<int>& cost) {
        if (step == _nSteps - 1 || step == _nSteps - 2) {
            // From last or 2nd last step, one can straightaway
            // jump to stair top
            return cost[step];
        }
        
        // Check if memoization table already has an entry
        // for reaching top of stairs from an earlier calc
        if (memoTbl[step] == -1) {
            // From step, one can jump to either step + 1 or step + 2
            // So to reach top from current step, min cost is sum of current step cost
            // and min of the cost from either step + 1 or step + 2
            int costToReachTopFromNextStep =
                minCostViaMemoization(memoTbl, step + 1, cost);
            int costToReachTopFromNextToNextStep =
                minCostViaMemoization(memoTbl, step + 2, cost);
            memoTbl[step] = cost[step] +
                min(costToReachTopFromNextStep, costToReachTopFromNextToNextStep);
        }
        
        return memoTbl[step];
    }
    
    int
    minCostDpIterative(vector<int>& cost) {
        // If current step is 'i', min cost to reach step 'i - 2'
        // (previous to previous step)
        int minCostToReachStepI_2 = 0;
        // If current step is 'i', min cost to reach step 'i - 1'
        // (previous step)
        int minCostToReachStepI_1 = 0;
        // Min cost to reach current step 'i'
        int minCostToReachStepI = 0;
        
        // Each step 'i' can be reached from either step 'i - 2' or
        // step 'i - 1'. So, to reach step 'i' with min cost; we need
        // to select one step from amongst the steps 'i - 1'/'i - 2'
        // whichever can be reached with minimum cost - in ordere to
        // reduce overall cost
        for (int currStep = 0; currStep < _nSteps; ++currStep) {
            // Compute cost to reach current step
            minCostToReachStepI =
                cost[currStep] +
                min(minCostToReachStepI_2, minCostToReachStepI_1);
            
            // Advancing to next step; so current step becomes previous.
            // Update the min costs to reach previous 2 steps
            minCostToReachStepI_2 = minCostToReachStepI_1;
            minCostToReachStepI_1 = minCostToReachStepI;
        }
        
        // Top floor is beyond final step. It can be reached from any of
        // the previous 2 steps (i.e. last 2 steps)
        return min(minCostToReachStepI_2, minCostToReachStepI_1);
    }
    
    // Data members
    int _nSteps;
};
