class Solution {
public:
    int
    totalFruit(vector<int>& fruits) {
        // Problem reduces to finding the maximum contiguous streak of
        // fruit trees whose fruits can fit into at most 2 baskets
        // OR the maximum contiguous streak of fruit trees which has
        // a maximum of 2 fruits
        // Above problem easily reduces to finding the maximum contiguous
        // subarray (fruit trees) which has a maximum of 2 different elements
        // (2 different fruits). This is easily solvable using a sliding window
        
        typedef vector<int>::size_type vecSzT;
        vecSzT nTrees = fruits.size();
        // Hash table mapping the different fruit types in the current
        // contiguous subarray of fruit trees to their respective counts
        unordered_map<int, int> basketToCntTbl;
        vecSzT sWinStart = 0;
        vecSzT maxSubArrLen = 0;
        // Iterate over the fruit trees sequentially. Contiguous block of
        // fruit trees from which fruits are are being pick is represented
        // by the sliding window close range [sWinStart, sWinEnd]
        // Add a new fruit tree from the right of the window at each step
        // for plucking the fruits
        for (vecSzT sWinEnd = 0; sWinEnd < nTrees; ++sWinEnd) {
            
            // Add current fruit to appropriate basket (each
            // different fruit has its own basket of unlimited size)
            basketToCntTbl[fruits[sWinEnd]]++;
        
            while (basketToCntTbl.size() > 2) {
                // Number of baskets exceeds 2. Dump the fruits plucked
                // from window start by shrinking the window from left;
                // till window holds 2 kinds of fruits
                auto & fruitAtWinStart = fruits[sWinStart];
                basketToCntTbl[fruitAtWinStart]--;
                if (basketToCntTbl[fruitAtWinStart] == 0) {
                    basketToCntTbl.erase(fruitAtWinStart);
                }
                // Shrink window from left
                ++sWinStart;
            }
            
            // Update the contiguous fruit tree length
            maxSubArrLen = max(maxSubArrLen, sWinEnd - sWinStart + 1);
        }
        
        return maxSubArrLen;
    }
};
