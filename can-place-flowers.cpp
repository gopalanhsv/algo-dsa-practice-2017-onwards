// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    bool
    canPlaceFlowers(vector<int>& flowerbed, int n) {
        if (0 == n) {
            return true;
        }
        
        // Flowers can be only planted on empty (0) plots and in a non-adjacent
        // manner (no consecutive flowers)
        // Move over flowerbeds from left to right. Employ the greedy method at
        // each step of planting a flowers at earliest seen empty flowerbed
        // as per constraints
        int fbSize = flowerbed.size();
        for (int fbId = 0; fbId < fbSize;) {
            if (flowerbed[fbId] == 1) {
                // Non-empty flowerbed
                // Skip this and next flower bed
                fbId += 2;
            } else {
                // Empty flowerbed
                // Check if adjacent flower beds are empty
                if (fbId == fbSize - 1 ||
                    flowerbed[fbId + 1] == 0) {
                    
                    // Plant a flower here
                    --n;
                    if (0 == n) {
                        // Done planting all flowers
                        return true;
                    }
                    // Skip this and next flowerbed
                    fbId += 2;
                } else {
                    // Next flower bed non empty
                    // Skip 3 consecutive flowerbeds from current
                    fbId += 3;
                }
            }
        }
        
        // Not able to plant all flowers
        return false;
    }
};
