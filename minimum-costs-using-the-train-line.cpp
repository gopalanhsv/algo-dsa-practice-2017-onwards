// n => regular.size()

// DP Approach
// Time complexity : O(n)
// Space complexity : O(n)

// DP Optimized Approach
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    vector<long long>
    minimumCosts(vector<int>& regular, vector<int>& express, int expressCost) {
        //return minimumCostsViaBottomDP(regular, express, expressCost);
        return minimumCostsViaBottomDPOptimized(regular, express, expressCost);
    }
    
private:
    
    vector<long long>
    minimumCostsViaBottomDP(vector<int>& regular, vector<int>& express, int expressCost) {

        int nStops = regular.size() + 1;
        
        vector<long long> minCostRegTbl(nStops + 1);
        vector<long long> minCostExpTbl(nStops + 1);
        vector<long long> minCostTbl(nStops - 1);
        
        minCostRegTbl[0] = 0;
        minCostExpTbl[0] = minCostRegTbl[0] + expressCost;
        for (int stopId = 1; stopId < nStops; ++stopId) {
            
            // Cost along regular route to current stop from previous stop
            // (both the stops are on regular route only)
            auto & regRouteCost = regular[stopId - 1];
            // Cost along express route to current stop from previous stop
            // (both the stops are on express route only)
            auto & expRouteCost = express[stopId - 1];
            
            minCostRegTbl[stopId] = 
                min(minCostRegTbl[stopId - 1] + regRouteCost, 
                    minCostExpTbl[stopId - 1] + expRouteCost);
            
            minCostExpTbl[stopId] = 
                min(minCostRegTbl[stopId] + expressCost, 
                    minCostExpTbl[stopId - 1] + expRouteCost);
            
            minCostTbl[stopId - 1] =
                min(minCostRegTbl[stopId], minCostExpTbl[stopId]);
        }
        
        return minCostTbl;
    }
    
    vector<long long>
    minimumCostsViaBottomDPOptimized(
        vector<int>& regular, vector<int>& express, int expressCost) {
    
        int nStops = regular.size() + 1;
        
        vector<long long> minCostTbl(nStops - 1);
        
        long long minCostToPrevRegStop = 0;
        long long minCostToPrevExpStop = minCostToPrevRegStop + expressCost;
        
        for (int stopId = 1; stopId < nStops; ++stopId) {
            
            // Cost along regular route to current stop from previous stop
            // (both the stops are on regular route only)
            auto & regRouteCost = regular[stopId - 1];
            
            // Cost along express route to current stop from previous stop
            // (both the stops are on express route only)
            auto & expRouteCost = express[stopId - 1];
            
            long long costToCurrRegStop = minCostToPrevRegStop + regRouteCost;
            long long costToCurrExpStop = minCostToPrevExpStop + expRouteCost;
            
            long long minCostToCurrRegStop = 
                min(costToCurrRegStop, costToCurrExpStop);
            
            long long minCostToCurrExpStop =
                min(minCostToCurrRegStop + expressCost, costToCurrExpStop);
            
            minCostTbl[stopId - 1] =
                min(minCostToCurrRegStop, minCostToCurrExpStop);
            
            minCostToPrevRegStop = minCostToCurrRegStop;
            minCostToPrevExpStop = minCostToCurrExpStop;
        }
        
        return minCostTbl;
    }
};
