class Solution {
public:
    int
    numTrees(int n) {
        return numUniqueBstViaDp(n);        
    }
    
private:
    int
    numUniqueBstViaDp(int maxNumberOfNodes) {
        // Table holding the number of unique BSTs which can be
        // generated for a given number of unique nodes
        vector<int> numUniqueBstsTbl(maxNumberOfNodes + 1, 0);

        // Number of unique BSTs with no nodes (single empty subtree)
        numUniqueBstsTbl[0] = 1;
        // Number of unique BSTs with 1 node
        numUniqueBstsTbl[1] = 1;
        
        // Use DP to successively determine the number of unique BSTs which
        // can be built for a given max number of unique nodes 'n', using
        // the number of BSTs which can built using 1,2,..,n-2,n-1 nodes
        for (int numNodes = 2; numNodes <= maxNumberOfNodes; ++numNodes) {
            // NBST(i) = num unique BSTs with i nodes
            // NBST(r, i) = num unique BSTs with i nodes with root r
            // Number of unique BSTs which can be built using a given
            // root with value 'r' for 'n' number of nodes would be
            // number of unique left bst subtrees which can be built using nodes from 1 to r-1 
            // multiplied by
            // number of unique right bst subtrees which can be built using nodes from r+1 to n
            // NBST(r, n) = NBST(r - 1) * NBST(n - r)

            // Iterate over all possible root values and determine the unique
            // number of BSTs can be constructed for each of the root values
            for (int root = 1; root <= numNodes; ++root) {
                numUniqueBstsTbl[numNodes] +=
                    numUniqueBstsTbl[root - 1] * numUniqueBstsTbl[numNodes - root];
            }
        }      

        return numUniqueBstsTbl[maxNumberOfNodes];
    }
};
