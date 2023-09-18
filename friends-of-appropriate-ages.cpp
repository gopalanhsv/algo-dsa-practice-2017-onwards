// n => ages.size()

// Hash table approach
// Time complexity : O(n)
// Space complexity : O(1) [as there are only 120 unique ages]

// Sorting + Binary search approach
// Time complexity : O(nlogn)
// Space complexity : O(logn)

class Solution {
public:
    int
    numFriendRequests(vector<int>& ages) {
        return numFriendRequestsViaSorting(ages);
        return numFriendRequestsViaHashTable(ages);
    }
    
private:
    
    int
    numFriendRequestsViaHashTable(vector<int>& ages) {
        // Build frequency count table for each age
        unordered_map<int, int> ageFreqCntTbl;
        for (auto & age : ages) {
            ageFreqCntTbl[age]++;
        }
        
        int nTotalRequests = 0;
        // Iterate over all possible pairs of ages
        for (auto & xAgeEntry : ageFreqCntTbl) {
            auto & xAge = xAgeEntry.first;
            auto & xAgeCnt = xAgeEntry.second;
            for (auto & yAgeEntry : ageFreqCntTbl) {
                auto & yAge = yAgeEntry.first;
                auto & yAgeCnt = yAgeEntry.second;
                
                // Check people of age 'xage' can send friend requests to
                // people of age 'yage'
                if ((yAge <= xAge) && (yAge > (xAge * .5 + 7))) {
                    // People of 'xage' can send requests to people of 'yage'
                    // Compute the number of friend requests
                    int nRequests;
                    if (xAge != yAge) {
                        nRequests = (xAgeCnt * yAgeCnt);
                    } else {
                        nRequests = ((xAgeCnt - 1) * yAgeCnt);
                    }
                    // Update the total number of requests
                    nTotalRequests += nRequests;
                }
            }
        }
        
        return nTotalRequests;
    }
    
    int
    numFriendRequestsViaSorting(vector<int>& ages) {
        // Sort the ages in ascending order
        sort(ages.begin(), ages.end());
        
        // Iterate over each pearson
        int nRequests = 0;
        for (auto currAge : ages) {
            
            // Compute lowest age of a person to whom current person can send a request
            int lowerBound = (currAge / 2) + 7;
            lowerBound += 1;
            // Compute highest age of a person to whom current person can send a request
            int upperBound = currAge;
            // Determine the smallest index to which the current person can sent request to
            auto lbIter = lower_bound(ages.begin(), ages.end(), lowerBound);
            // Determine the largest index to which the current person can sent request to
            auto ubIter = upper_bound(ages.begin(), ages.end(), upperBound);
            // Current person can send requests on to people in range [lbIter, ubIter] excluding self-request
            int currNumRequests = ubIter - lbIter - 1;
            // Normalize the number of request to avoid -1 and update the number of possible requests
            nRequests += max(0, currNumRequests);
        }
        
        return nRequests;
    }
};
