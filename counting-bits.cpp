// Simple approach
// Time complexity: O(nlogn)
// Space complexity: O(n) for result otherwise O(1)

// DP approach
// Time complexity: O(n)
// Space complexity: O(n)

class Solution {
public:
    vector<int>
    countBits(int n) {
        //return countBitsSimple(n);
        return countBitsDP(n);
    }
    
private:
    
    vector<int>
    countBitsSimple(int num) {
        vector<int> nBitsV(num + 1, 0);
        // Iterate over each number sequentially in range [1, n]
        for (int i = 1; i <= num; ++i) {
            int n = i;
            int bitCnt = 0;
            // Determine the number of bits in number 'i' and update it
            while (n) {
                // Clear the rightmost/least significant set bit of number
                n = n & (n - 1);
                ++bitCnt;
            }
            nBitsV[i] = bitCnt;
        }
        return nBitsV;
    }
    
    vector<int>
    countBitsDP(int num) {
        vector<int> nBitsV(num + 1, 0);
        for (int i = 1; i <= num; ++i) {
            // n & (n - 1) will clear the rightmost/least significant set bit of number 'n'
            // So the number 'n & (n - 1)' will have 1 bit lesser than number 'n'
            // Hence, num bits in 'n' = num bits in 'n & (n - 1)' + 1
            nBitsV[i] = nBitsV[i & (i - 1)] + 1;
        }
        return nBitsV;
    }
    
};
