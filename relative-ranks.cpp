// n => score.size()
// Heap Sort Approach
// Time complexity : O(nlogn)
// Space complexity : O(n)

// Map/Ordered table Approach
// Time complexity : O(nlogn)
// Space complexity : O(n)

class Solution {
public:
    vector<string>
    findRelativeRanks(vector<int>& score) {
        //return ranksViaMapApproach(score);
        return ranksViaHeapSortApproach(score);
    }
    
private:
    
    vector<string>
    ranksViaHeapSortApproach(vector<int>& score) {
        // Construct a max heap of <score, index position of score in score array>
        // tuples sorted in descending order of scores
        struct scoreCmpObj {
            bool
            operator()(const pair<int, int> & p1, const pair<int, int> & p2) {
                return p1.first < p2.first;
            }
        };
        priority_queue<pair<int, int>, vector<pair<int, int> >, scoreCmpObj> maxHeap;

        for (auto i = 0; i != score.size(); ++i) {
            maxHeap.push({score[i], i});
        }
        
        // Withdraw elements from heap on basis of score, find the position as
        // to where ranks should be written in output array and assign ranks
        vector<string> rankV(score.size());
        if (!maxHeap.empty()) {
            auto & he = maxHeap.top(); // he =>heap entry
            rankV[he.second] = "Gold Medal";
            maxHeap.pop();
        }
        if (!maxHeap.empty()) {
            auto & he = maxHeap.top(); // he =>heap entry
            rankV[he.second] = "Silver Medal";
            maxHeap.pop();
        }
        if (!maxHeap.empty()) {
            auto & he = maxHeap.top(); // he =>heap entry
            rankV[he.second] = "Bronze Medal";
            maxHeap.pop();
        }
        int rank = 4;
        while (!maxHeap.empty()) {
            auto & he = maxHeap.top(); // he =>heap entry
            rankV[he.second] = to_string(rank++);
            maxHeap.pop();
        }
        
        return rankV;
    }
    
    vector<string>
    ranksViaMapApproach(vector<int>& score) {
        // Populate table of scores mapped to their location indices in the array. Set
        // up the map s.t. it is kept sorted in non-increasing order of scores
        map<int, int, greater<int> > scoresToIdxTbl;
        for (int i = 0; i != score.size(); ++i) {
            scoresToIdxTbl[score[i]] = i;
        }
        
        vector<string> outV(score.size());
        // Iterate over the scores in descending order of their values
        // Find corresponding location in output vector and populate the
        // location with appropriate rank
        auto it = scoresToIdxTbl.begin();
        // 1st three ranks given medals
        if (it != scoresToIdxTbl.end()) {
            outV[it->second] = "Gold Medal";
            ++it;
        }
        if (it != scoresToIdxTbl.end()) {
            outV[it->second] = "Silver Medal";
            ++it;
        }
        if (it != scoresToIdxTbl.end()) {
            outV[it->second] = "Bronze Medal";
            ++it;
        }
        // 4th rank onwards
        auto endIt = scoresToIdxTbl.end();
        int rank = 4;
        for (; it != endIt; ++it, ++rank) {
            outV[it->second] = to_string(rank);
        }
        
        return outV;
    }
    
};
