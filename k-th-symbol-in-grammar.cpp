// Recursive Approach
// Time complexity : O(log n)
// Space complexity : O(log n) for stack space

// Bitset Approach
// Time complexity : O(1)
// Space complexity : O(1)

class Solution {
public:
    int
    kthGrammar(int N, int K) {
        //return kthGrammarRecursiveApproach1(N, K);
        return kthGrammarBitsetApproach(N, K);
    }
    
private:
    int
    kthGrammarRecursiveApproach1(int n, int k) {
        // When the rows for the kth grammar are arranged in form of tree,
        // it forms a binary tree structure with the first half of a row 'n'
        // being identical to row 'n - 1'; and second half of a row 'n' being
        // the 1's complement of first half
        // Using the above fact, we have the following recurrence relation:-
        
        // T(n, k) => kth bit position in nth row
        // T(n, k) = T(n - 1, k) if k lies in 1st half of a row, 
        // T(n, k) = toggle T(n - 1, k - num elems in half of the row), if k lies
        // in 2nd half of row (i.e advancing k to be in 1st half and invert result)
        // T(n, k) = 0 if n = 1 or k = 1, termination condition
        // toggling instead of negation as negation will make leading unused 0s as 1
        
        if (1 == n || 1 == k) {
            // Termination condition
            return 0;
        }
        
        // Num elements in row N (1-indexed) is 2 ^ (N - 1)
        int nElemsInHalfRow = 1 << (n - 2); // (2 ^ (N - 1)) / 2
        if (k <= nElemsInHalfRow) {
            // K in 1st half of the row
            return kthGrammarRecursiveApproach1(n - 1, k);
        }
        // K in 2nd half of the row
        return 1 ^ kthGrammarRecursiveApproach1(n - 1, k - nElemsInHalfRow);
    }
    
    int
    kthGrammarBitsetApproach(int n, int k) {
        // When the rows for the kth grammar are arranged in form of
        // tree, it forms a binary tree structure with the following properties :--
        // If x/k is 0 indexed, and f(n, x) is value of x th bit for nth row
        // f(n, x) determines f(n + 1, 2x) and f(n + 1, 2x + 1)
        
        // if f(x) = 0 at row n, f(2x) = 0 & f(2x + 1) = 1 at row n + 1
        // if f(x) = 1 at row n, f(2x) = 1 & f(2x + 1) = 0 at row n + 1
        
        // i.e the bit gets flipped for odd locations of 'k' and stays same
        // for even locations of 'k' for successive rows
        // f(2x) = f(x) ^ 0  & f(2x + 1) = f(x) ^ 1 where x and 2x are in successive rows
        // If we represent x in binary as shown below
        // f(10001011) = f(1000101) ^ 1 = f(100010) ^ 1 ^ 1 = f(1000) ^ 0 ^ 1 ^ 1 =
        // f(100) ^ 0 ^ 0 ^ 1 ^ 1 = f(10) ^ 0 ^ 0 ^ 0 ^ 1 ^ 1 = f(1) ^ 0 ^ 0 ^ 0 ^ 0 ^ 1 ^ 1
        // = 1 ^ 0 ^ 0 ^ 0 ^ 0 ^ 1 ^ 1 or XOR of all bits of x. Since XOR or 0 does
        // nothing, this reduces to XOR of all 1 bits; or in other words result 
        // would be 1 if number of bits is odd or 0 if even
        return bitset<32>(k - 1).count() & 1;
    }
};
