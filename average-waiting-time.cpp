// n => customers.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    double
    averageWaitingTime(vector<vector<int>>& customers) {
        if (customers.empty()) {
            return 0;
        }
        
        long totalWaitingTime = 0;
        long currTime = customers[0][0];
        for (auto & ent : customers) {
            auto & arrivalTime = ent[0];
            auto & prepTime = ent[1];
            long waitingTimeForChefToBeAvl = max(0L, currTime - arrivalTime);
            long waitingTime = waitingTimeForChefToBeAvl + prepTime;
            
            totalWaitingTime += waitingTime;
            
            currTime = arrivalTime + waitingTime;
        }
        
        return double(totalWaitingTime) / customers.size();
    }
};
