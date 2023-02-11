class Solution {
public:
    long long
    pickGifts(vector<int>& gifts, int k) {
        // Gifts are kept in a PQ with piles have more gifts
        // prior to the piles have lesser gifts (i.e. maxHeap)
        priority_queue<int, vector<int>, less<int> > maxHeap;
        
        // Dump all gifts into the PQ and add up all the gifts
        long long totalGifts = 0;
        for (auto & pile : gifts) {
            maxHeap.push(pile);
            totalGifts += pile;
        }
        
        // Each second, take out gifts from the pile with max gifts
        // till 'k' seconds elapse or all gifts are exhausted
        while (!maxHeap.empty() && (k-- > 0)) {
            
            // Select pile with most gifts
            int selectedGifts = maxHeap.top();
            maxHeap.pop();
            
            // Select the gifts to be left behind
            int leftGifts = floor(sqrt(selectedGifts));
            // Dump back left behind gifts to PQ
            if (leftGifts > 0) {
                maxHeap.push(leftGifts);
            }
            // Deduct the taken gifts from total gifts
            int takenGifts = selectedGifts - leftGifts;
            totalGifts -= takenGifts;
        }

        return totalGifts;
    }
};
