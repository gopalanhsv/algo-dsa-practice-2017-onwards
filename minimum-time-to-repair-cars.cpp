// r => ranks.size()
// min => min_element(ranks)
// max => max_element(ranks)
// Time Complexity : O(rlog(max - min))
// Space Complexity : O(1)

class Solution {
public:
    long long
    repairCars(vector<int>& ranks, int cars) {
        int minRank = ranks[0];
        int maxRank = ranks[0];
        for (auto & rank : ranks) {
            minRank = min(rank, minRank);
            maxRank = max(rank, maxRank);
        }
        long long minPossibleRepairTime = (long long)minRank;
        long long maxPossibleRepairTime = (long long)maxRank * cars * cars;
        
        long long hi = maxPossibleRepairTime;
        long long lo = minPossibleRepairTime;
        while (lo < hi) {
            long long mid = lo + (hi - lo) / 2;
            if (possibleToRepairAllCars(ranks, cars, mid)) {
                hi = mid;
            } else {
                lo = mid + 1;
            } 
        }
        
        return lo;
    }
    
private:
    
    bool
    possibleToRepairAllCars(vector<int>& ranks, int nCarsReqdToBeRepaired, long long avlTime) {
        int nTotalCarsRepaired = 0;
        for (auto & rank : ranks) {
            long long timeToRepairOneCar = rank;
            int nCarsRepaired = sqrt(avlTime / timeToRepairOneCar);
            nTotalCarsRepaired += nCarsRepaired;
            if (nTotalCarsRepaired >= nCarsReqdToBeRepaired) {
                return true;
            }
        }
        
        return nTotalCarsRepaired >= nCarsReqdToBeRepaired;
    }
};
