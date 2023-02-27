/*
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;
    
    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/

class Solution {
public:
    Node*
    construct(vector<vector<int>>& grid) {
        int gridLen = grid.size();
        if ((0 == gridLen) || (gridLen != grid[0].size())) {
            // Error : Empty OR rectangular grid
            return nullptr;
        }
        
        // Build the quadtree for the grid via divide and conquer
        return buildQTreeForSubGrid(grid, 0, 0, gridLen);
    }
    
private:
    
    Node*
    buildQTreeForSubGrid(
        vector<vector<int>>& grid, int leftIdx, int topIdx, int sideLen) {
        
        if (1 == sideLen) {
            // Single cell grid => Represented as a single node
            // quad tree which is both a leaf and tree root
            bool nodeVal = (1 == grid[leftIdx][topIdx]);
            return new Node(nodeVal, true);
        }

        // Divide current square grid into 4 disjoint equal sized square subgrids 
        // Construct the quad tree (aka subtree) for each of these 4 subgrids
        int subGridSideLen = (sideLen >> 1);
        auto topLeftSubtree =
            buildQTreeForSubGrid(grid, leftIdx,
                                 topIdx, subGridSideLen);
        auto topRightSubtree =
            buildQTreeForSubGrid(grid, leftIdx,
                                 topIdx + subGridSideLen, subGridSideLen);
        auto bottomLeftSubtree =
            buildQTreeForSubGrid(grid, leftIdx + subGridSideLen,
                                 topIdx, subGridSideLen);
        auto bottomRightSubtree =
            buildQTreeForSubGrid(grid, leftIdx + subGridSideLen,
                                 topIdx + subGridSideLen, subGridSideLen);
        
        // Combine the 4 quad-subtrees representing the 4 disjoint subgrids
        // and form the quad-tree root node for the current grid
        
        if (topLeftSubtree->isLeaf && topRightSubtree->isLeaf &&
            bottomLeftSubtree->isLeaf && bottomRightSubtree->isLeaf) {
            
            // Current subgrid has four subtrees which are all leaves
            
            if ((topLeftSubtree->val == topRightSubtree->val) &&
                (bottomLeftSubtree->val == bottomRightSubtree->val) &&
                (topLeftSubtree->val == bottomRightSubtree->val) ) {
                // Current subgrid has four subtrees which are all leaves having
                // the same value (i.e. all elements in the current grid have the
                // same value => current grid can be represented as a single leaf
                // node quadtree
                #if 0
                // Deleting the quad subtrees for the 4 equal-sized subgrids
                // as they are superseded by a single node
                delete topLeftSubtree;
                delete topRightSubtree;
                delete bottomLeftSubtree;
                delete bottomRightSubtree;
                #endif
                bool nodeVal = topLeftSubtree->val;
                return new Node(nodeVal, true);
            }
        }
        
        // Create the root node for the quadtree representing the current grid;
        // with its 4 children being the subtree roots of the 4 quad-subtrees
        // representing the disjoint equalsized subgrids of current grid
        return new Node(false, false,
                        topLeftSubtree, topRightSubtree,
                        bottomLeftSubtree, bottomRightSubtree);
        
    }
};
