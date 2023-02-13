class Solution {
public:
    int
    countOdds(int low, int high) {
    
        // Number of elements in [low, high]
        int nElements = high + 1 - low;
        // Pair up 2 adjacent numbers starting from 'low' till 'high'
        
        // If number of elements is even, pairing will happen like
        // like (low, low + 1), (low + 2, low + 3)......till
        // (high - 3, high - 2), (high - 1, high). There will be equal
        // number of odd and even numbers. So number of odds and evens
        // will be half of the total number of elements
        if (0 == (nElements & 0x1)) {
            return nElements >> 1;
        }

        // If number of elements is odd, pairing will happen like
        // like (low, low + 1), (low + 2, low + 3)......till
        // (high - 2, high - 1), high. 'high' is left unpaired.
        // So number of odds and evens will depend on whether 'low' is odd/even
        // if 'low' is odd, all pairs will have an odd number and 'high' 
        // also will be odd.
        // if 'low' is even, all pairs will have an odd number and 'high'
        // be even
        int nPairs = nElements >> 1;
        
        return (low & 0x1) ? nPairs + 1 : nPairs;
    }
};
