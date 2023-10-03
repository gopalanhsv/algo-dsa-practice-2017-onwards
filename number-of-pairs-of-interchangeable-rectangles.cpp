// n => rectangles.size()
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    long long
    interchangeableRectangles(vector<vector<int>>& rectangles) {
        // Two rectangles at indices i and j with i < j form an interchangeable pair if each
        // of them has the same width/height ratio
        
        // Have a hash table maintaining frequency count of width-to-height ratio of all
        // rectangles. Rectangles grouped against the same hash table entry are interchangeable
        
        long long totalPairs = 0;
        unordered_map<double, long long> ratioToFreqCntTbl;
        // Iterate over the rectangles from L->R and populate the hash table for each rectangle
        for (auto & rectangle : rectangles) {
            auto & w = rectangle[0];
            auto & h = rectangle[1];
            // VIMP (Extremely important to static cast here to long;
            // else ratios will be computed in truncated integer form)
            double whRatio = (double)w / h;
            
            // Check if there are rectangles seen earlier with the same width-to-height ratio
            auto iter = ratioToFreqCntTbl.find(whRatio);
            if (iter != ratioToFreqCntTbl.end()) {
                // Rectangle(s) with same W2H ratio has/have been seen earlier
                // Current rectangle will form an interchangeable pair
                // with each prior instance of a rectangle with the same W2H ratio
                // => number of interchangeable pairs formed by current rectangle is the 
                // current frequency count of W2H ratio
                long long nPairs = iter->second;
                // Update the total number of interchangeable pairs
                totalPairs += nPairs;
            }
            // Update frequency count of rectangles with current W2H ratio
            ratioToFreqCntTbl[whRatio]++;
        }
        
        return totalPairs;
    }
};
