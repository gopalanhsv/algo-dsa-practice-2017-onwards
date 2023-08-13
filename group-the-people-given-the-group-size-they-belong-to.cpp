// n => groupSizes.size()
// Time complexity : O(n)
// Space complexity : O(n)
class Solution {
public:
    vector<vector<int>>
    groupThePeople(vector<int>& groupSizes) {
        vector<vector<int> > outV;
        
        // Hash table used for group construction
        // Maps group size to the list/array of member ids who belong
        // to a group of the particular size
        unordered_map<int, vector<int> > sizeToGroupMembersTbl;
        
        // Iterate through each person/member id sequentially
        for (auto mId = 0; mId != groupSizes.size(); ++mId) {
            // Current member 'mId' group size
            auto groupSz = groupSizes[mId];
            // Add current member to group of appropriate size
            sizeToGroupMembersTbl[groupSz].emplace_back(mId);
            
            // Current group of appropriate size with the current member added
            auto & currentGroupV = sizeToGroupMembersTbl[groupSz];
            
            if (currentGroupV.size() == groupSz) {
                // Current group of appropriate size is full
                // Add current group to output
                outV.emplace_back(currentGroupV);
                // Empty the current group in hash table to get it ready for
                // next fill with new members
                currentGroupV.clear();
            }            
        }
        
        return outV;
    }
};
