// n => arr.size()

// DP Bottom Up Tabulation Approach
// Time complexity : O(nlogn + n^2)
// Space complexity : O(n)

const int moduloFactor = 1000000000 + 7;

class Solution {
public:
    int
    numFactoredBinaryTrees(vector<int>& arr) {
        return numFactoredBinaryTreesDPBottomUpDP(arr);
    }
    
private:

    int
    numFactoredBinaryTreesDPBottomUpDP(vector<int>& arr) {
        
        // 1. Since each integer is g.t 1 and each internal node is the product of the
        //    values of its child nodes; the values of internal nodes will be g.t those
        //    of its children
        // 2. If nWays[x] is the number of ways to build an internal node of a tree
        //    with value 'x'; we get nWays[x] = nWays[y] x nWays[z], where x = y * z
        //    for all possible values of 'y' & 'z'

        // Since each array value is unique, due to condition (1) & (2); subtree nodes will
        // always have lower values compared to that of their ancestors. Compute the number
        // of subtrees possible with smaller values and use these subtrees to build up larger
        // trees in a recursive fashion via DP
        
        // Arrange potential node vals in ascending order
        sort(arr.begin(), arr.end());
        auto arrSz = arr.size();
        
        // Hash table of candidate binary tree node vals (as all are unique)
        unordered_set<int> nodeVals(arr.begin(), arr.end());
        
        long long nTotalBinaryTrees = 0;
        // dpTbl[i] is the number of ways in binary trees with factors can be
        // constructed with a root value 'i'
        unordered_map<int, long long> dpTbl;
        // Iterate over each candidate root val in ascending order
        for (auto & rootVal : arr) {
            
            // Num ways to build binary tree with current root val
            // initialized to a single node tree
            long long nWays = 1;
            
            // Iterate over all candidate left subtree values for given root
            // (these have to be factors of root and hence will be l.t. root val)
            for (auto & leftSubtreeRootVal : arr) {
                
                if (0 != rootVal % leftSubtreeRootVal) {
                    // Node with current candidate left subtree root value cannot
                    // is a non-factor => binary tree not possible with given left subtree
                    continue;
                }
                
                if ((long long)leftSubtreeRootVal * leftSubtreeRootVal > (long long) rootVal) {
                    // Skipping computation for symmetric factors as they would have been
                    // accounted for earlier by 2x factor
                    continue;
                }
                
                // Since left child and right child values must be factors of the root,
                // check for presence of candidate right subtree root value in array
                auto rightSubtreeRootVal = rootVal / leftSubtreeRootVal;
                auto iter = nodeVals.find(rightSubtreeRootVal);
                if (nodeVals.end() != iter) {
                    // Binary tree with root value 'rootVal' and its subtrees as 
                    // 'leftSubtreeRootVal' & 'rightSubtreeRootVal' possible
                    // Number of such binary trees will be the products of the number of
                    // left and right subtrees
                    if (leftSubtreeRootVal == rightSubtreeRootVal) {
                        // Left and right subtree roots are same and hence not interchangeable
                        nWays += (dpTbl[leftSubtreeRootVal] * dpTbl[rightSubtreeRootVal]);
                    } else {
                        // 2x factor to account for left and right subtree roots being interchangeable
                        nWays += (2 * dpTbl[leftSubtreeRootVal] * dpTbl[rightSubtreeRootVal]);
                    }
                    nWays %= moduloFactor;
                }
            }
            
            // Update the number of binary trees with current candidate root val 
            dpTbl[rootVal] = nWays; 
            // Update the total number of binary trees
            nTotalBinaryTrees += nWays;
            nTotalBinaryTrees %= moduloFactor;
        }
        
        return nTotalBinaryTrees;
    }
};
