// r => number of requests
// n => number of buildings
// Time complexity : O(n x (2 ^ r))
// Space complexity : O(n + r)

class Solution {
public:
    int
    maximumRequests(int n, vector<vector<int>>& requests) {
        if (0 == n || 0 == requests.size()) {
            // Base case of nil buildings/requests
            return 0;
        }
        
        // Initialize
        _nRequests = requests.size();
        _netEmployeeChangesPerBuildingV.resize(n, 0);
        _maxAchievableRequests = 0;
        
        // Attempt all possible permutations of transfer requests via DFS and backtracking
        // in order to find the combinations which result in nil net transfers
        transferRequestsDfsHelper(requests, 0, 0);

        return _maxAchievableRequests;
    }
    
private:
    
    void
    transferRequestsDfsHelper(vector<vector<int> >& requestsV, int currRequestId, int nActiveRequests) {
        
        if (currRequestId == _nRequests) {
            // All requests in the current permutation have been processed
            // Check if the current permutation of requests results in zero net change in transfers
            for (auto & netEmployeeChanges : _netEmployeeChangesPerBuildingV) {
                if (netEmployeeChanges != 0) {
                    // Current permutation of requests results in non-zero net change
                    // in employee transfer in some building(s) which is not allowed 
                    return;
                }
            }
            
            // Current permutation of requests results in zero net change in employee
            // transfers across all buildings. Update the max number of requests resulting in
            // net zero tranfers to account for the current set of active requests resulting
            // in the required state
            _maxAchievableRequests = max(nActiveRequests, _maxAchievableRequests);
            return;
        }

        // There are two options with the current request :
        
        // Option#1 : Current transfer request is allowed
        // Allow the transfer request - adjust the number of employees at the request endpoints
        // and the number of allowed active requests
        auto & currRequest = requestsV[currRequestId];
        auto & from = currRequest[0];
        _netEmployeeChangesPerBuildingV[from]--;
        auto & to = currRequest[1];
        _netEmployeeChangesPerBuildingV[to]++;
        // Process the subsequent requests recursively
        transferRequestsDfsHelper(requestsV, currRequestId + 1, nActiveRequests + 1);
        // Backtrack and restore the state prior to allowing current request
        _netEmployeeChangesPerBuildingV[from]++;
        _netEmployeeChangesPerBuildingV[to]--;
        
        // Option#2 : Skip current transfer request
        // Process the subsequent requests recursively
        transferRequestsDfsHelper(requestsV, currRequestId + 1, nActiveRequests);
    }
    
    // Data members
    
    // Number of requests
    int _nRequests;
    // Array tracking the net change in employees due to tranfers on a per
    // building basis during DFS + backtracking
    vector<int> _netEmployeeChangesPerBuildingV;
    // Tracks the max number of achievable transfer requests resulting in
    // in zero net transfers amongst all possible request permutations seen so far 
    int _maxAchievableRequests;
};
